#include "isoscelesTriangle.h"

IsoscelesTriangle::~IsoscelesTriangle() {}
IsoscelesTriangle::IsoscelesTriangle(const Point & top, double angle, double side) 
	: Triangle(top, Point(top.x - side * sin(to_radian(angle) / 2), top.y - side * cos(to_radian(angle) / 2)),
		Point(top.x + side * sin(to_radian(angle) / 2), top.y - side * cos(to_radian(angle) / 2)))
{
	try_catch_isosceles_triangle();
}

IsoscelesTriangle::IsoscelesTriangle(const Point & top,double angle, double side, std::string red, std::string green, std::string blue)
	: Triangle(top, Point(top.x - side * sin(to_radian(angle) / 2), top.y - side * cos(to_radian(angle) / 2)),
		Point(top.x + side * sin(to_radian(angle) / 2), top.y - side * cos(to_radian(angle) / 2)), red, green, blue)
{
	try_catch_isosceles_triangle();
}

IsoscelesTriangle::IsoscelesTriangle(const IsoscelesTriangle & other) : Triangle(other) 
{
		try_catch_isosceles_triangle();
}


void IsoscelesTriangle::out(std::ostream & out_) const
{
	out_ << "I am isosceles triangle!\n";
	out_ << "Sides: " << a << "; " << b << "; " << c << std::endl;
	Polygon::out(out_);
}

bool IsoscelesTriangle::isItNotIsoscelesTriangle() const
{
	if ((a != c) || Triangle::isItNotTriangle()) throw std::invalid_argument("It is not Isosceles Triangle. Error!\n");
	return ((a != c) || Triangle::isItNotTriangle()); 
}

void IsoscelesTriangle::try_catch_isosceles_triangle()
{
	try
	{
		isItNotIsoscelesTriangle();
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}

void IsoscelesTriangle::scale(double coef)
{
	Triangle::scale(coef);
	try_catch_isosceles_triangle();
}

void IsoscelesTriangle::rotate(double angle)
{
	Triangle::rotate(angle);
	try_catch_isosceles_triangle();
}

void IsoscelesTriangle::move(const Point & p)
{
	Triangle::move(p);
	try_catch_isosceles_triangle();
}