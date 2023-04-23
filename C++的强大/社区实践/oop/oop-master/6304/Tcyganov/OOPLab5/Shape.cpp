#include "Shape.h"


Point Shape::getCenter()
{
    Point c;
    c.x = (this->p1.x + this->p2.x)/2.0;
    c.y = (this->p1.y + this->p2.y)/2.0;
    return c;
}

float Shape::toRadian(int degree)
{
	return degree * M_PI / 180;
}

void Shape::Rotate(int angle)
{
	float radAngle = toRadian(angle);
	Point c = getCenter();
	Point P1;
	Point P2;
	P1.x = ((this->p1.x - c.x) * cos(radAngle) - (this->p1.y - c.y) * sin(radAngle)) + c.x;
	P1.y = ((this->p1.x - c.x) * sin(radAngle) + (this->p1.y - c.y) * cos(radAngle)) + c.y;

	P2.x = ((this->p2.x - c.x) * cos(radAngle) - (this->p2.y - c.y) * sin(radAngle)) + c.x;
	P2.y = ((this->p2.x - c.x) * sin(radAngle) + (this->p2.y - c.y) * cos(radAngle)) + c.y;

	this->p1 = P1;
	this->p2 = P2;
}

float Shape::Perimeter()
{
	return 0.0f;
}

Shape::Shape(Point p1, Point p2) : p1(p1), p2(p2)
{ 
	this->color = "Black";
}


Shape::~Shape()
{
}
