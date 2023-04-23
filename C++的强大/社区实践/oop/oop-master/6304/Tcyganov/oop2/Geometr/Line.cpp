#include "Line.h"

void Line::MoveTo(float x, float y)
{
	this->p2.x += (x - this->p1.x);
	this->p2.y += (y - this->p1.y);

	this->p1.x = x;
	this->p1.y = y;
}

void Line::Scale(float value)
{
	Point c = getCenter();
	this->p1.x = ((c.x - this->p1.x) * value) + c.x;
	this->p1.y = ((c.y - this->p1.y) * value) + c.y;

	this->p2.x = ((c.x - this->p2.x) * value) + c.x;
	this->p2.y = ((c.y - this->p2.y) * value) + c.y;
}


Line::Line(Point p1, Point p2) : Shape(p1, p2) { }


Line::~Line()
{
}

std::ostream& operator<<(std::ostream& os, const Line& line)
{
	os << "Line ("
		<< line.p1.x << "; "
		<< line.p1.y << ") ("
		<< line.p2.x << "; "
		<< line.p2.y << ")"
		<< " Color: " << line.color;
	return os;
}