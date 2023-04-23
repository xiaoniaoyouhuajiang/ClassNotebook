#pragma once
#include "Shape.h"

class Square : public Shape
{
	double side;
public:
	Square(Point center, double side) : Shape(center)
	{
		this->side = side;
		points.push_back(Point((center.getX() - side / 2), (center.getY() - side / 2)));
		points.push_back(Point((center.getX() - side / 2), (center.getY() + side / 2)));
		points.push_back(Point((center.getX() + side / 2), (center.getY() + side / 2)));
		points.push_back(Point((center.getX() + side / 2), (center.getY() - side / 2)));
	}
	void scale(int k);
	void printOUT(std::ostream& out);
};