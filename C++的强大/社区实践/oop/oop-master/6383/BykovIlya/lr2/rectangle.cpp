#include "rectangle.h"

Rectangle::Rectangle() : Polygon() {}
Rectangle::~Rectangle() {}
Rectangle::Rectangle(const Point & top, double a, double b)
	: Polygon({ top, Point(top.get_x() + a, top.get_y()), 
		Point(top.get_x() + a, top.get_y() - b), Point(top.get_x(), top.get_y() - b) }), a(a), b(b) 
{
	try_catch_rectangle();
}

Rectangle::Rectangle(const Point & top, double a, double b,  std::string red, std::string green, std::string blue) 
	: Polygon({ top, Point(top.get_x() + a, top.get_y()), 
		Point(top.get_x() + a, top.get_y() - b), Point(top.get_x(), top.get_y() - b) }, red, green, blue), a(a), b(b) 
{
	try_catch_rectangle();
}

Rectangle::Rectangle(const Rectangle & other) : Polygon(other), a(other.a), b(other.b) 
{
	try_catch_rectangle();
}

Rectangle & Rectangle::operator = (const Rectangle & other)
{
	if (this != &other)
		Rectangle(other).swap(*this);
	return *this;
}


double Rectangle::get_a() const { return a; }
double Rectangle::get_b() const { return b; }
double & Rectangle::get_a() { return a; }
double & Rectangle::get_b() { return b; }
double Rectangle::perimeter() const
{
	return 2 * (a + b);
}
double Rectangle::area() const
{
	return a * b;
}
void Rectangle::scale(double coef)
{
	a *= coef;
	b *= coef;
	Polygon::scale(coef);
	try_catch_rectangle();
}

void Rectangle::rotate(double angle)
{
	Polygon::rotate(angle);
	try_catch_rectangle();
}

void Rectangle::move(const Point & p)
{
	Polygon::move(p);
	try_catch_rectangle();
}

void Rectangle::out(std::ostream & out_) const
{
	out_ << "I am rectangle!\n";
	out_ << "Sides: " << a << "; " << b << std::endl;
	Polygon::out(out_);
}

bool Rectangle::isItNotRectangle() const
{
	bool res = tops[0].equationOfTheLine(tops[1], tops[2]) ||  tops[1].equationOfTheLine(tops[2], tops[3]) 
		|| tops[0].equationOfTheLine(tops[1], tops[3]);
	if (res || tops.size() != 4) throw std::invalid_argument("It is not Rectangle. Error!\n");
	return (res || tops.size() != 4);
}

void Rectangle::try_catch_rectangle()
{
	try
	{
		isItNotRectangle();
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}

void Rectangle::swap(Rectangle & other)
{
	Polygon::swap(other);
	//Colour::swap(other.colour);
	std::swap(a, other.a);
	std::swap(b, other.b);
}