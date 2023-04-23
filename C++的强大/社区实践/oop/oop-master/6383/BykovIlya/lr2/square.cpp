#include "square.h"

Square::Square() : Rectangle() {}
Square::~Square() {}
Square::Square(const Point & top, const double x) : Rectangle(top, x, x) 
{
	try_catch_square();
}

Square::Square(const Point & top, const double x, std::string red, std::string green, std::string blue) : Rectangle(top, x, x, red, green, blue) 
{
	try_catch_square();
}

Square::Square(const Square & other) : Rectangle(other)
{
	try_catch_square();	
}

void Square::out(std::ostream & out_) const
{
	out_ << "I am square!\n";
	out_ << "Side: " << a << std::endl;
	Polygon::out(out_);
}

bool Square::isItNotSquare() const
{
	if (( a != b) || Rectangle::isItNotRectangle()) throw std::invalid_argument("It is not Square. Error!\n");
	return ( a != b) || Rectangle::isItNotRectangle();
}

void Square::try_catch_square()
{
	try
	{
		isItNotSquare();
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}

void Square::scale(double coef)
{
	Rectangle::scale(coef);
	try_catch_square();
}

void Square::rotate(double angle)
{
	Rectangle::rotate(angle);
	try_catch_square();
}

void Square::move(const Point & p)
{
	Rectangle::move(p);
	try_catch_square();
}

