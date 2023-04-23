#include "Shape.h"


Point Shape::getCenter()
{
	float x = this->p1.x + this->p2.x;
	float y = this->p1.y + this->p2.y;
	return Point{ (float)(x / 2.0), (float)(y / 2.0) };
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

Shape::Shape(Point p1, Point p2) : p1(p1), p2(p2)
{ 
	this->color = "Black";
}


Shape::~Shape()
{
}
