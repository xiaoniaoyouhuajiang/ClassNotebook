#include "triangle.h"

Triangle::Triangle() : Polygon() {}
Triangle::~Triangle() {}
Triangle::Triangle(const Point & p_1, const Point & p_2, const Point & p_3) : Polygon(std::vector<Point>({ p_1, p_2, p_3 }))
{
	try_catch_triangle();
	a = p_1.length(p_2);
	b = p_2.length(p_3);
	c = p_3.length(p_1);
	
}

Triangle::Triangle(const Point & p_1, const Point & p_2, const Point & p_3, std::string red, std::string green, std::string blue) 
	: Polygon(std::vector<Point>({ p_1, p_2, p_3 }), red, green, blue)
{
	try_catch_triangle();
	a = p_1.length(p_2);
	b = p_2.length(p_3);
	c = p_3.length(p_1);
}

Triangle::Triangle(const Triangle & other) : Polygon(other), a(other.a), b(other.b), c(other.c) 
{
	try_catch_triangle();	
}

Triangle & Triangle::operator = (const Triangle & other)
{
	if (this != &other)
		Triangle(other).swap(*this);
	return *this;
}


void Triangle::scale(double coef)
{
	a *= coef;
	b *= coef;
	c *= coef;
	Polygon::scale(coef);
	try_catch_triangle();
}

void Triangle::rotate(double angle)
{
	Polygon::rotate(angle);
	try_catch_triangle();
}

void Triangle::move(const Point & p)
{
	Polygon::move(p);
	try_catch_triangle();
}

double Triangle::perimeter() const
{
	return a + b + c;
}
double Triangle::area() const
{
	return sqrt(perimeter() / 2 * (perimeter() / 2 - a) * (perimeter() / 2 - b) * (perimeter() / 2 - c));
}

void Triangle::out(std::ostream & out_) const
{
	out_ << "I am triangle!\n";
	out_ << "Sides: " << a << "; " << b << "; " << c << std::endl;
	Polygon::out(out_);
}

bool Triangle::isItNotTriangle() const
{
	if (tops[0].equationOfTheLine(tops[1], tops[2]) || (tops.size() != 3)) throw std::invalid_argument("It is not Triangle. Error!\n");
	return tops[0].equationOfTheLine(tops[1], tops[2]) || (tops.size() != 3);
}

void Triangle::try_catch_triangle()
{
	try
	{
		isItNotTriangle();
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}

void Triangle::swap(Triangle & other)
{
	Polygon::swap(other);
//	Colour::swap(other.colour);
	std::swap(a, other.a);
	std::swap(b, other.b);
	std::swap(c, other.c);
}

double Triangle::get_a() const { return a; }
double Triangle::get_b() const { return b; }
double Triangle::get_c() const { return c; }
double & Triangle::get_a() { return a; }
double & Triangle::get_b() { return b; }
double & Triangle::get_c() { return c; }
