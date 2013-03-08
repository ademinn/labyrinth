#pragma once
#include <QGLWidget>
#include <QtCore>
#include <QtGui>
#include "labyrinth.h"
#include "quaternion.h"

class GLWidget : public QGLWidget
{
	//Q_OBJECT;
	QTimer *timer;
    GLdouble const distance;
    Quaternion lastPosition;
    Quaternion curPosition;
    Vector curVector;
    double const radius;
	const double time;
	Vector pos;
	Vector v;
	Vector g;
    Labyrinth o;

    void rotate(int x, int y);
    void calcCurVector(int x, int y);

public:
    GLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
	void updateScene();
};