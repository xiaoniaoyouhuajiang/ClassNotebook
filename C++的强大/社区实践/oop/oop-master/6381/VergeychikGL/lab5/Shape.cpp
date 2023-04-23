
#include "Shape.h"

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}
double Point::getX()
{
	return x;
}
double Point::getY()
{
	return y;
}
void Point::setX(double x)
{
	this->x = x;
}
void Point::setY(double y)
{
	this->y = y;
}

void Shape::move(Point newCenter)
{
	double changeX = newCenter.getX() - center.getX(), changeY = newCenter.getY() - center.getY();
	for (int i = 0; i < points.size(); i++)
	{
		points[i].setX(points[i].getX() + changeX);
		points[i].setY(points[i].getY() + changeY);
	}
}
void Shape::turn(int angle)
{
	this->angle += angle % 360;
	double angleRad = angle*PI / 180;
	for (int i = 0; i < points.size(); i++)
	{
		double newX = points[i].getX()*cos(angleRad) - points[i].getY()*sin(angleRad);
		double newY = points[i].getX()*sin(angleRad) + points[i].getY()*cos(angleRad);
		points[i].setX(newX);
		points[i].setY(newY);
	}
}
void Shape::zoom(int k)
{
	if (k<0) {
		k = abs(k);
	}
	center.setX(center.getX() * k);
	center.setY(center.getY() * k);
	for (auto& i : points) {
		i.setX(i.getX() * k);
		i.setY(i.getY() * k);
	}
}
Point Shape::getCenter()
{
	return center;
}
void Shape::setColor(std::string color) {
	this->color = color;
}
std::string Shape::getColor()
{
	return color;
}

