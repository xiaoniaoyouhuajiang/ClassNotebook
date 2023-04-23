#include "point.h"
#include <cmath>

double point::getX() const
{
	return x;
}

double point::getY() const
{
	return y;
}

void point::setX(double x)
{
	this->x = x;
}

void point::setY(double y)
{
    this->y = y;
}

double point::len() const {
    return sqrt(x * x + y * y);
}
point::point(double x, double y) : x(x), y(y) {}

point::point() : point(0, 0) {}

point::point(const point& other) : point(other.x, other.y) {}
point& point::operator=(const point& other) {
    x = other.x;
    y = other.y;
    return *this;
}

point& point::operator+=(const point &b) {
    x += b.x;
    y += b.y;
    return *this;
}
point& point::operator-=(const point &b) {
    x -= b.x;
    y -= b.y;
    return *this;
}

point& point::operator*=(double val) {
    x *= val;
    y *= val;
    return *this;
}
point& point::operator/=(double val) {
    x /= val;
    y /= val;
    return *this;
}

point operator+(point a, const point& b) {
    return a += b;
}
point operator-(point a, const point& b) {
    return a -= b;
}
point operator*(point a, double val) {
    return a *= val;
}
point operator/(point a, double val) {
    return a /= val;
}


