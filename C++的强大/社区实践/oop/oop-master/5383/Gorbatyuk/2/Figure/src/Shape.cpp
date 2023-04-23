#include "stdafx.h"
#include "Shape.h"

#define PI 3.14159265  

int Shape::counter = 0;

Shape::Shape(Color _color)
{
	this->currentColor = _color;
	id = counter++;
}


bool Shape::IsInsideOfAnother(const Shape & other)
{
	return false;
}


Color::Color()
{
}
