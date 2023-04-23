#include "Circle.h"

Circle::Circle(double input_radius, Point &cntr, Color &clr) : radius(input_radius), Shape(cntr, clr) {}

const double Circle::Get_Radius() const { return radius; }

void Circle::Calibr(double calibr) { radius *= calibr; }

void Circle::Move(double x, double y) {
	cntr.x = x;
	cntr.y = y;
}

ostream& operator <<(ostream &os, const Circle &c) {
	os << "R=" << c.Get_Radius() << endl;
	os << (const Shape &)c;
	return os;
}
