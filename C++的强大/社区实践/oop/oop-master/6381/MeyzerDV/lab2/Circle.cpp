#include "Circle.hpp"

double Circle::getRadius() const
{
	return this->R;
}

void Circle::setRadius(double newR)
{
	this->R = newR;
}

void Circle::print() const
{
	std::cout << "Printing circle object with ID " << getID() << std::endl;
	std::cout << "It's position: " << Pos.x << " " << Pos.y << " " << Pos.z << std::endl;
	std::cout << "It's color: " << Color.x << " " << Color.y << " " << Color.z << " " << std::endl;
	std::cout << "It's angle: " << Angle << std::endl;
	std::cout << "It's radius: " << R << std::endl;
}

void Circle::scale(double sc)
{
	R*=sc;
}
