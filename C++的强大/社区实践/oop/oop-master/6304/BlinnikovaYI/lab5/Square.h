#pragma once
#include "Shape.h"

class Square : public Shape {
public:
	Square(Point center, double side) : Shape(center.x, center.y), side(side) {
		points.push_back({ center.x - side / 2, center.y + side / 2 });
		points.push_back({ center.x + side / 2, center.y + side / 2 });
		points.push_back({ center.x + side / 2, center.y - side / 2 });
		points.push_back({ center.x - side / 2, center.y - side / 2 });
	}

	void zoom(double n);

	void printOUT(ostream& out);

private:
	double side;
};
