#include "basis.h"

Point::Point()
{
	x = 0.0;
	y = 0.0;
}

Point::Point(double _x, double _y)
	: x(_x), y(_y)
{
}

void Point::Set_X(double _x)
{
	x = _x;
}

void Point::Set_Y(double _y)
{
	y = _y;
}

double Point::Get_X() const
{
	return this->x;
}

double Point::Get_Y() const
{
	return this->y;
}

Colour::Colour(const int red, const int green, const int blue)
{
	Red = red;
	Blue = blue;
	Green = green;
}

void Colour::SetColour(int _Red, int _Green, int _Blue)
{
	Red = _Red;
	Green = _Green;
	Blue = _Blue;
}

int Colour::GetRed() const
{
	return Red;
}

int Colour::GetGreen() const
{
	return Green;
}

int Colour::GetBlue() const
{
	return Blue;
}

Point operator+(const Point & lhs, const Point & rhs)
{
	return Point(lhs.Get_X() + rhs.Get_X(), lhs.Get_Y() + rhs.Get_Y());
}

Point operator-(const Point & lhs, const Point & rhs)
{
	return Point(lhs.Get_X() - rhs.Get_X(), lhs.Get_Y() - rhs.Get_Y());
}

ostream& operator<<(ostream & stream, const Colour& rgb)
{
	stream << "Red = " << rgb.GetRed()
		<< " Green = " << rgb.GetGreen()
		<< " Blue = " << rgb.GetBlue() << endl;
	return stream;
}

ostream & operator<<(ostream & stream, const Point & p)
{
	stream << "x = " << p.Get_X() << ", y = " << p.Get_Y();
	return stream;
}