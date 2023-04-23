#pragma once
#include "Shape.h"
class Ellipse : public Shape
{
	int radiusX, radiusY;

public:
	Ellipse(Point center, int radiusX, int radiusY) : Shape(center.x, center.y), radiusX(radiusX), radiusY(radiusY) {

		points.push_back(Point((center.x - radiusX), center.y));
		points.push_back(Point(center.x, (center.y + radiusY)));
		points.push_back(Point((center.x + radiusX), center.y));
		points.push_back(Point(center.x, (center.y - radiusY)));
	}

	void zoom(double n);

	void printOUT(ostream& out);

};
