#include "Ellipse.h"
#include <cmath>

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

float Ellipse::Perimeter()
{
	float res = 0.0f;
	Point c = getCenter();
	Point a;
	Point b;
	a.x=((this->p1.x + this->p2.x)/2);
	a.y = this->p1.y;
	b.y = ((this->p1.y + this->p2.y) / 2);
	a.x = this->p2.x;
	float dl1;
	float dl2;
	dl1= sqrt(pow(c.x - a.x, 2)+pow(c.x - a.x, 2));
	dl2 = sqrt(pow(c.x - b.x, 2) + pow(c.x - b.x, 2));
	
	res = 2 * M_PI * sqrt((pow(dl1, 2) + pow(dl2, 2))/2);
	return res;
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
