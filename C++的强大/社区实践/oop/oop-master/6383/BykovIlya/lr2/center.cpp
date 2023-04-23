#include "center.h"

Point::Point() : x(0), y(0) {}
Point::~Point() {}
Point::Point(double x, double y) : x(x), y(y) {}
Point::Point(const Point & p) : x(p.x), y(p.y) {}
Point::Point(Point && p) { if (this != &p) swap(p); } 
Point & Point::operator = (const Point & p) { if (this != &p) Point(p).swap(*this); return *this;}
Point & Point::operator = (Point && p) { if (this != &p) swap(p); return *this; }
Point Point::operator += (const Point & p) { return Point(x += p.x, y += p.y); }
Point Point::operator -= (const Point & p) { return Point(x -= p.x, y -= p.y); }
Point Point::operator *= (const Point & p) { return Point(x *= p.x, y *= p.y); }
Point Point::operator *= (const double value) { return Point(x *= value, y *= value); }
Point Point::operator /= (const Point & p) { return Point(x /= p.x, y /= p.y); }
Point Point::operator /= (const double value) { return Point(x /= value, y /= value); }
Point Point::operator + (const Point & p) const { return Point(x + p.x, y + p.y); }
Point Point::operator - (const Point & p) const { return Point(x - p.x, y - p.y); }
Point Point::operator * (const double value) const { return Point(x * value, y * value); }
Point Point::operator / (const double value) const { return Point(x / value, y / value); }
Point Point::operator + () { return *this; }
Point Point::operator - () { return Point(x * (-1), y * (-1)); }
const bool Point::operator == (const Point & p) { return ((x == p.x) && (y = p.y)) ? true : false; }
double Point::get_x() const { return x; }
double Point::get_y() const { return y; }
double & Point::get_x() { return x; }
double & Point::get_y() { return y; }
void Point::set_x(const double & x) { this->x = x; }
void Point::set_y(const double & y) { this->y = y; }
double Point::abs() const { return sqrt(x * x + y * y); }

void Point::rotate(double angle)	 											
{
	double _x = x;
	double _y = y;
	x = _x * cos(angle) - _y * sin(angle);			// использыем матрицу поворота	cosx	-sinx
	y = _x * sin(angle) + _y * cos(angle);			//								sinx	cosx
}

double Point::length(const Point & p)	const										
{
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

void Point::scale(const double coef)												
{
	(*this) *= coef;
}

void Point::move(const Point & p)
{
	(*this) += p;
}

void Point::swap(Point & p)
{
	std::swap(x, p.x);
	std::swap(y, p.y);
}

std::ostream & operator << (std::ostream & out_, const Point & p)
{
	p.out(out_);
}

void Point::out(std::ostream & out_) const
{
	out_ << "( " << x << " , " << y  << " )  ";
}

bool Point::equationOfTheLine(const Point & p1, const Point & p2) const
{
	return  ((p2.x - x) * (p1.y - y) == (p2.y - y) * (p1.x - x));
}

