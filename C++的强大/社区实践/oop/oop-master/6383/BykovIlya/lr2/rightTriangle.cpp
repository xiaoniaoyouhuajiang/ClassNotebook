#include "rightTriangle.h"

RightTriangle::RightTriangle(const Point & top, const double catheter_1, const double catheter_2)
	:Triangle(top, Point(top.x + catheter_1, top.y), Point(top.x, top.y + catheter_2))
{
	try_catch_right_triangle();
}

RightTriangle::RightTriangle(const Point & top, const double catheter_1, const double catheter_2, std::string red, std::string green, std::string blue)
		:Triangle(top, Point(top.x + catheter_1, top.y), Point(top.x, top.y + catheter_2), red, green, blue)
{
	try_catch_right_triangle();
}

RightTriangle::RightTriangle(const RightTriangle & other) : Triangle(other)
{
	try_catch_right_triangle();
}

RightTriangle::~RightTriangle() {}

double RightTriangle::area() const
{
	return (get_a() * get_b() / 2);
}

void RightTriangle::out(std::ostream & out_) const
{
	out_ << "I am right triangle!\n";
	out_ << "Sides: " << get_a() << "; " << get_b() << "; " << get_c() << std::endl;
	Polygon::out(out_);
}

bool RightTriangle::isItNotRightTriangle() const
{
	if ((get_b() * get_b() != get_a() * get_a() + get_c() * get_c()) || Triangle::isItNotTriangle()) throw std::invalid_argument("It is not Right Triangle. Error!\n");\
	return ((get_b() * get_b() != get_a() * get_a() + get_c() * get_c()) || Triangle::isItNotTriangle());
}
void RightTriangle::try_catch_right_triangle()
{
	try
	{
		isItNotRightTriangle();
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}

void RightTriangle::scale(double coef)
{
	Triangle::scale(coef);
	try_catch_right_triangle();
}

void RightTriangle::rotate(double angle)
{
	Triangle::rotate(angle);
	try_catch_right_triangle();
}

void RightTriangle::move(const Point & p)
{
	Triangle::move(p);
	try_catch_right_triangle();
}