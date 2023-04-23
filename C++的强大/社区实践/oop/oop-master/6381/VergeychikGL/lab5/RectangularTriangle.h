#pragma once
#include "Shape.h"

class rectangularTriangle : public Shape
{
	double side;
	double side2;
public:
	rectangularTriangle(Point center, double side, double side2) : Shape(center)
	{
		this->side = side;
		this->side2 = side2;
		double side3 = sqrt(side*side + side2*side2);
		double r = (side + side2 - side3) / 2;
		points.push_back(Point((center.getX() - r), (center.getY() - r)));
		points.push_back(Point((center.getX() - r), (center.getY() + side - r)));
		points.push_back(Point((center.getX() - r + side2), (center.getY() - r)));
	}
	void scale(int k);
	void printOUT(std::ostream& out);
};