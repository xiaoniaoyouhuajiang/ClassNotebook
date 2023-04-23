#include "point.h"
#include <locale>
#include <iostream>

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}


bool Point::distance(const Point &smth) const
{
	double dx = smth.x - x;
	double dy = smth.y - y;
	return sqrt(dx*dx + dy*dy);
}