#include <QtCore>
#include <QtGui>
#include "glwidget.h"
#include "matrix.h"
#include "quaternion.h"

void rotate1(Vector &, Vector const &, double const);
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    GLWidget *window = new GLWidget;
    window->show();
    return app.exec();
	/*Vector v(1, 0, 0);
	Vector n(0, 0, 1);
	double ang = 2 * pi;
	//rotate(v, Quaternion(n, ang));
	rotate1(v, n, ang);
	std::cout << v.x() << " " << v.y() << " " << v.z() << '\n';
	int tmp;
	std::cin >> tmp;
	return 0;*/
}
void rotate1(Vector &vect, Vector const &q, double const a)
{
	Vector v = q;
	Vector u = v / abs(v);
	//std::cout << v.x() << " " << v.y() << " " << v.z() << '\n';
	//double a = q.getAngle() * pi / 180;
	std::cout << a << '\n';
	std::vector< std::vector<double> > s1;
	s1.resize(3);
	for(int i = 0; i < 3; ++i)
		s1[i].resize(3);
	s1[0][0] = 0;	s1[0][1] = -u.z();	s1[0][2] = u.y();
	s1[1][0] = u.z();	s1[1][1] = 0;		s1[1][2] = -u.x();
	s1[2][0] = -u.y();	s1[2][1] = u.x();	s1[2][2] = 0;
	Matrix S(s1);
	Matrix U(u);
	Matrix M = U + cos(a) * (I - U) + sin(a) * S;
	vect = M * vect;
}
