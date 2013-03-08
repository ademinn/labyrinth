#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget *parent)
    :QGLWidget(parent), distance(30.0), lastPosition(Id), curPosition(Id), curVector(0.0, 0.0, 1.0), radius(3.0), pos(0.0, 15.0, 0.0), v(0.0, 0.0, 0.0), g(0.0, -9.8, 0.0), time(0.015), o(3)
{
	GLfloat amb_color[] = {0.2f, 0.2f, 0.2f, 1};
    GLfloat dif_color[] = {0.2f, 0.2f, 0.2f, 1};
    GLfloat spec_color[] = {0.1f, 0.1f, 0.1f, 1};
	Material tmp(amb_color, dif_color, spec_color);
	//o = labyrinth(5, 2, tmp);
	/*o = sphere(1, 3, tmp);*/
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer->start(10);
}

void GLWidget::rotate(int x, int y)
{
	/*y = height() - y;
	Vector v1((2 * radius * (x - width() / 2) / width()), (2 * radius * (y - height() / 2) / height()), radius);
	Vector n = multiply(curVector, v1);
	double ang = angle(curVector, v1);
	curVector = v1;
	Quaternion q(n, ang);
	curPosition = q;
	curPosition.normalize();*/
	int px = x;
	int py = height() - y;
	Vector tmp((2 * radius * (px - width() / 2) / width()), (2 * radius * (py - height() / 2) / height()), radius);
	//std::cout << px * px + py * py << '\n';
	curVector = tmp;
	o.chDir(curVector);
}

void GLWidget::calcCurVector(int x, int y)
{
	lastPosition = curPosition * lastPosition;
    lastPosition.normalize();
	curPosition = Id;
	int px = x;
	int py = height() - y;
	Vector tmp((2 * radius * (px - width() / 2) / width()), (2 * radius * (py - height() / 2) / height()), radius);
	curVector = tmp;
	o.setDir(curVector);
}

void GLWidget::initializeGL()
{
    glClearColor(0.6f, 0.6f, 0.6f, 0.0f);
    GLfloat position[] = {20.0f, 20.0f, distance - 20, 1.0f};
	GLfloat ambient[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0 * width / 500, 2.0 * width / 500, -2.0 * height / 500, 2.0 * height / 500, 5, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL()
{
	//time += 0.01;
	//Vector tmp = pos + g * time * time / 2;
	v += g * time;
	pos += v * time + g * time * time / 2;
	if(pos.y() - 1 < -15)
	{
		v = -v;
		v *= 0.8;
		pos = Vector(0.0, -14.0, 0.0);
		//std::cout << v.x() << " " << v.y() << " " << v.z() << '\n';
	}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -distance);
	//glRotated(curPosition.getAngle(), curPosition.getVector().x(), curPosition.getVector().y(), curPosition.getVector().z());
	//glRotated(lastPosition.getAngle(), lastPosition.getVector().x(), lastPosition.getVector().y(), lastPosition.getVector().z());
	o.paintLab();
	/*Object o1 = sphere(5, 1);
	o1.paint();
	Object o2 = sphere(5, 2);
	glTranslated(5, 0, 0);
	o2.paint();*/
	/*glBegin(GL_POLYGON);
	glNormal3dv(-g);
	glVertex3d(-20.0, -15.0, 20.0);
	glNormal3dv(-g);
	glVertex3d(20.0, -15.0, 20.0);
	glNormal3dv(-g);
	glVertex3d(20.0, -15.0, -20.0);
	glNormal3dv(-g);
	glVertex3d(-20.0, -15.0, -20.0);
	glEnd();
	glTranslated(pos.x(), pos.y(), pos.z());
	o.paint();*/
	glFlush();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() == Qt::LeftButton) || (event->buttons() == Qt::RightButton))
        rotate(event->x(), event->y());
    //updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    calcCurVector(event->x(), event->y());
}


/*void GLWidget::updateScene()
{
	h -= 0.5;
	updateGL();
}*/