#include "Ellipse.h"


Ellipse::Ellipse(Point p1, Point p2) : Shape(p1, p2) { }

void Ellipse::MoveTo(float x, float y)
{	
	this->p2.x += (x - this->p1.x);
	this->p2.y += (y - this->p1.y);

	this->p1.x = x;
	this->p1.y = y;
}

void Ellipse::Scale(float value)
{
	Point c = getCenter();
	this->p1.x = ((c.x - this->p1.x) * value) + c.x;
	this->p1.y = ((c.y - this->p1.y) * value) + c.y;

	this->p2.x = ((c.x - this->p2.x) * value) + c.x;
	this->p2.y = ((c.y - this->p2.y) * value) + c.y;
}


Ellipse::~Ellipse() { }

std::ostream & operator<<(std::ostream & os, const Ellipse & ellipse)
{
	os << "Ellipse ("
		<< ellipse.p1.x << "; "
		<< ellipse.p1.y << ") ("
		<< ellipse.p2.x << "; "
		<< ellipse.p2.y << ")"
		<< " Color: " << ellipse.color;
	return os;
}
