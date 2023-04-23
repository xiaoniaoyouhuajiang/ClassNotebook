#include "Ellipse.h"

Ellipse::Ellipse(Point f1, Point f2, double input_a, Point &cntr, Color &clr) : F1(f1), F2(f2), a(input_a), Shape(cntr, clr) {}

const double Ellipse::Get_a() const { return a; }

const Point& Ellipse::Get_F1() const { return F1; }

const Point& Ellipse::Get_F2() const { return F2; }

const double Ellipse::Get_c() const {
	return sqrt((F1.x - cntr.x)*(F1.x - cntr.x) + (F1.y - cntr.y)*(F1.y - cntr.y));
}

void Ellipse::Calibr(double calibr) {
	a *= calibr;
	F1.x = cntr.x + (F1.x - cntr.x)*calibr;
	F1.y = cntr.y + (F1.y - cntr.y)*calibr;
	F2.x = cntr.x + (F2.x - cntr.x)*calibr;
	F2.y = cntr.y + (F2.y - cntr.y)*calibr;
}

void Ellipse::Grad(double grad) {
	double c = Get_c();
	F1.x = c*cos(grad/180 * PI ) + cntr.x;
	F2.x = c*(-1)*cos(grad / 180 * PI)+ cntr.x;
	F1.y = c*sin(grad / 180 * PI) + cntr.y;
	F2.y = c*sin(-1*grad / 180 * PI) + cntr.y;
}

void Ellipse::Move(double x, double y) {
	F1.x = F1.x - cntr.x + x;
	F1.y = F1.y - cntr.y + y;
	F2.x = F2.x - cntr.x + x;
	F2.y = F2.y - cntr.y + y;
	cntr.x = x;
	cntr.y = y;

}

ostream& operator <<(ostream &os, const Ellipse &c) {
	Point f1 = c.Get_F1();
	Point f2 = c.Get_F2();
	os << "a=" << c.Get_a();
	os << " F1(" << f1.x << "," << f1.y << ")";
	os << " F2(" << f2.x << "," << f2.y << ")" << endl;
	os << (const Shape &)c;
	return os;
}
