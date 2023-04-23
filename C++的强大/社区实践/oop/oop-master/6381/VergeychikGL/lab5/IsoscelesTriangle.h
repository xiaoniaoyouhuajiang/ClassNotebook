#pragma once
#include "Shape.h"

class isoscelesTriangle : public Shape
{
	double side;
	double side2;
	int angleOfTriangle;
public:
	isoscelesTriangle(Point center, double side, int angle) : Shape(center)
	{
		this->side = side;
		this->angleOfTriangle = angle;
		side2 = 2 * side*(1 - cos(angle*PI / 180));
		double r = side2*sin((180 - angle) / 2)*sin((180 - angle) / 2) / cos(angle / 2);
		double h = sqrt(side*side - side2*side2 / 4);
		points.push_back(Point((center.getX() - side2 / 2), (center.getY() - r)));
		points.push_back(Point((center.getX()), (center.getY() + h - r)));
		points.push_back(Point((center.getX() + side2 / 2), (center.getY() - r)));
	}
	void scale(int k);
	void printOUT(std::ostream& out);
};