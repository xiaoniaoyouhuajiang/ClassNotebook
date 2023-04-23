#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
	int sideA;
	int sideB;

public:
	Rectangle(Point center, int sideA, int sideB) : Shape(center.x, center.y), sideA(sideA), sideB(sideB)
	{
		points.push_back(Point((center.x - sideB / 2), (center.y + sideA / 2)));
		points.push_back(Point((center.x + sideB / 2), (center.y + sideA / 2)));
		points.push_back(Point((center.x + sideB / 2), (center.y - sideA / 2)));
		points.push_back(Point((center.x - sideB / 2), (center.y - sideA / 2)));
	}

	void zoom(double n);

	void printOUT(ostream& out);

};
