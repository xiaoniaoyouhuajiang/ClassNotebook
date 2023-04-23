#include "Shape.h"

Shape::Shape(Point cntr, Color clr) : cntr(cntr), clr(clr) {
	static int next_ID = 0;
	ID = next_ID++;
}

const Color& Shape::Get_Color() const { return clr; }

const Point& Shape::Get_Point() const { return cntr; }

const int Shape::Get_ID() const { return ID; }


ostream& operator <<(ostream &os, const Shape &c) {
	os << c.Get_ID() << "\n";
	os << '(' << c.cntr.x << ',' << c.cntr.y << ')' << " [" << c.clr.red << '|' << c.clr.green << '|' << c.clr.blue << "]\n";
	return os;
}
