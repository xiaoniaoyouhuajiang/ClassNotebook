#include "shape.h"
#include <algorithm>

size_t Shape::count = 0;

Shape::Shape()
{
	id = count++;
}

Shape::Shape(std::string red, std::string green, std::string blue) : Shape()
{
	colour = Colour(red, green, blue);
}

Shape::Shape(const Shape & other) : Shape()
{
	colour = other.colour;
}

Colour Shape::get_Colour() const 
{ 
	return colour; 
}

size_t Shape::get_ID() const
{ 
	return id; 
}

size_t & Shape::get_ID() { return id; }

std::ostream & operator << (std::ostream & out_, const Shape & shape)
{
	shape.out(out_);
	return out_;
}

