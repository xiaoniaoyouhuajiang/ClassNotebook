#include "Pentagon.h"


Point Pentagon::getCenter()
{
    Point c;
    c.x = (this->p1.x + this->p2.x + this->p3.x + this->p4.x + this->p5.x)/5.0;
    c.y = (this->p1.y + this->p2.y + this->p3.y + this->p4.y + this->p5.y)/5.0;
    return c;
}

Pentagon::Pentagon(Point p1, Point p2, Point p3, Point p4, Point p5) : Shape(p1, p2)
{
	this->p3 = p3;
	this->p4 = p4;
	this->p5 = p5;
}


void Pentagon::MoveTo(float x, float y)
{
	Point c = getCenter();

	p1.x += (x - c.x);
	p1.y += (y - c.y);

	p2.x += (x - c.x);
	p2.y += (y - c.y);

	p3.x += (x - c.x);
	p3.y += (y - c.y);

	p4.x += (x - c.x);
	p4.y += (y - c.y);

	p5.x += (x - c.x);
	p5.y += (y - c.y);
}

void Pentagon::Rotate(int angle)
{
	float radAngle = toRadian(angle);
	Point c = getCenter();
	Point P1;
	Point P2;
	Point P3;
	Point P4;
	Point P5;

	P1.x = ((this->p1.x - c.x) * cos(radAngle) - (this->p1.y - c.y) * sin(radAngle)) + c.x;
	P1.y = ((this->p1.x - c.x) * sin(radAngle) + (this->p1.y - c.y) * cos(radAngle)) + c.y;

	P2.x = ((this->p2.x - c.x) * cos(radAngle) - (this->p2.y - c.y) * sin(radAngle)) + c.x;
	P2.y = ((this->p2.x - c.x) * sin(radAngle) + (this->p2.y - c.y) * cos(radAngle)) + c.y;

	P3.x = ((this->p3.x - c.x) * cos(radAngle) - (this->p3.y - c.y) * sin(radAngle)) + c.x;
	P3.y = ((this->p3.x - c.x) * sin(radAngle) + (this->p3.y - c.y) * cos(radAngle)) + c.y;

	P4.x = ((this->p4.x - c.x) * cos(radAngle) - (this->p4.y - c.y) * sin(radAngle)) + c.x;
	P4.y = ((this->p4.x - c.x) * sin(radAngle) + (this->p4.y - c.y) * cos(radAngle)) + c.y;

	P5.x = ((this->p5.x - c.x) * cos(radAngle) - (this->p5.y - c.y) * sin(radAngle)) + c.x;
	P5.y = ((this->p5.x - c.x) * sin(radAngle) + (this->p5.y - c.y) * cos(radAngle)) + c.y;

	this->p1 = P1;
	this->p2 = P2;
	this->p3 = P3;
	this->p4 = P4;
	this->p5 = P5;
}

void Pentagon::Scale(float value)
{
	Point c = getCenter();
	p1.x = ((c.x - p1.x) * value) + c.x;
	p1.y = ((c.y - p1.y) * value) + c.y;

	p2.x = ((c.x - p2.x) * value) + c.x;
	p2.y = ((c.y - p2.y) * value) + c.y;

	p3.x = ((c.x - p3.x) * value) + c.x;
	p3.y = ((c.y - p3.y) * value) + c.y;

	p4.x = ((c.x - p4.x) * value) + c.x;
	p4.y = ((c.y - p4.y) * value) + c.y;

	p5.x = ((c.x - p5.x) * value) + c.x;
	p5.y = ((c.y - p5.y) * value) + c.y;
}

float Pentagon::Perimeter()
{
	float res = 0.0f;
	float dl1;
	float dl2;
	float dl3;
	float dl4;
	float dl5;
	dl1 = sqrt(pow(this->p2.x - this->p1.x, 2) + pow(this->p2.y - this->p1.y, 2));
	dl2 = sqrt(pow(this->p3.x - this->p2.x, 2) + pow(this->p3.y - this->p2.y, 2));
	dl3 = sqrt(pow(this->p4.x - this->p3.x, 2) + pow(this->p4.y - this->p3.y, 2));
	dl4 = sqrt(pow(this->p5.x - this->p4.x, 2) + pow(this->p5.y - this->p4.y, 2));
	dl5 = sqrt(pow(this->p1.x - this->p5.x, 2) + pow(this->p1.y - this->p5.y, 2));
	res = dl1 + dl2 + dl3 + dl4 + dl5;
	return res;
}

Pentagon::~Pentagon()
{
}

std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon)
{
	os << "Pentagon [("
		<< pentagon.p1.x << "; "
		<< pentagon.p1.y << "), ("
		<< pentagon.p2.x << "; "
		<< pentagon.p2.y << "), ("
		<< pentagon.p3.x << "; "
		<< pentagon.p3.y << "), ("
		<< pentagon.p4.x << "; "
		<< pentagon.p4.y << "), ("
		<< pentagon.p5.x << "; "
		<< pentagon.p5.y << ")]"
		<< " Color: " << pentagon.color;
	return os;
}
