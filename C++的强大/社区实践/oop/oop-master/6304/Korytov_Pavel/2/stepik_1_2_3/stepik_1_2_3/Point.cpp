#include "stdafx.h"
#include "Point.h"

void swap(Point & first, Point & second)
{
	swap(first.x, second.x);
	swap(first.y, second.y);
}

ostream & operator<<(ostream & os, const Point & p)
{
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

istream & operator >> (istream & is, Point & p)
{
	is >> p.x >> p.y;
	return is;
}

Point operator+(Point& p1, Point& p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator-(Point& p1, Point& p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point& Point::Rand(int min, int max)
{
	this->x = (min + rand() % (max - min));
	this->y = (min + rand() % (max - min));
	return *this;
}

Point & Point::operator=(Point p)
{
	swap(*this, p);
	return *this;
}

Point::Point(Point && p)
{
	swap(*this, p);
}

Point & Point::operator/(double i)
{
	x = x / i;
	y = y / i;
	return *this;
}

Point & Point::operator*(double i)
{
	x = x * i;
	y = y * i;
	return *this;
}
