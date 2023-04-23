#include "Shape.hpp"


const V3i& Shape::getColor() const
{
	return this->Color;
}
const V3d& Shape::getPos() const
{
	return this->Pos;
}
double Shape::getAngle() const
{
	return this->Angle;
}
int Shape::getID() const
{
	return this->ID;
}
void Shape::setColor(const V3i& newColor)
{
	this->Color = newColor;
	this->Color.x %= 256;
	this->Color.y %= 256;
	this->Color.z %= 256;
}
void Shape::setPos(const V3d& newPos)
{
	this->Pos = newPos;
}
void Shape::setAngle(double newAngle)
{
	this->Angle = newAngle;
}

std::ostream& operator<<(std::ostream& ostr, const Shape& s)
{
	s.print();
	return ostr;
}
