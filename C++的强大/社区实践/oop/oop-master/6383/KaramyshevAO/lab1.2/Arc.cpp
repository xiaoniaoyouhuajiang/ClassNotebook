#include "Arc.h"

Arc::Arc(Point p1, Point p2, double input_radius, Point &cntr, Color &clr) : P1(p1), P2(p2), Circle(input_radius, cntr, clr) {}

void Arc::Calibr(double calibr) {
	Circle::Calibr(calibr);
	P1.x = (P1.x - cntr.x)*calibr + cntr.x;
	P1.y = (P1.y - cntr.y)*calibr + cntr.y;
	P2.x = (P2.x - cntr.x)*calibr + cntr.x;
	P2.y = (P2.y - cntr.y)*calibr + cntr.y;
}

void Arc::Grad(double grad) {
	P1.x = cos(acos((P1.x - cntr.x) / radius) + (grad/180)*PI) + cntr.x;
	P1.y = sin(acos((P1.x - cntr.x) / radius) + (grad / 180)*PI) + cntr.y;
	P2.x = cos(acos((P2.x - cntr.x) / radius) + (grad / 180)*PI) + cntr.x;
	P2.y = sin(acos((P2.x - cntr.x) / radius) + (grad / 180)*PI) + cntr.y;
}
const Point& Arc::Get_P1() const { return P1; }

const Point& Arc::Get_P2() const { return P2; }

void Arc::Move(double x, double y) {
	P1.x = P1.x - cntr.x + x;
	P1.y = P1.y - cntr.y + y;
	P2.x = P2.x - cntr.x + x;
	P2.y = P2.y - cntr.y + y;
		Circle::Move(x, y);
}

ostream& operator <<(ostream &os, const Arc &c) {
	Point p1 = c.Get_P1();
	Point p2 = c.Get_P2();
	os << "P1(" << p1.x << "," << p1.y << ")";
	os << " P2(" << p2.x << "," << p2.y << ")" << endl;
	os << (const Circle &)c;
	return os;
}
