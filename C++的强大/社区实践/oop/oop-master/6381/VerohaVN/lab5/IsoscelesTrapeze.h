#pragma once
#include "Shape.h"

class IsoscelesTrapeze : public Shape {
	double height;
	double base1; //Lower
	double base2; //Upper
public:
	IsoscelesTrapeze(Point center, double _height, double _base1, double _base2) : Shape(center.x, center.y), height(_height), base1(_base1), base2(_base2) {
		points.push_back(Point(center.x, center.y + _height / 2));	//Upper center
		points.push_back(Point(center.x - base2 / 2, center.y + _height / 2));	//Upper Left
		points.push_back(Point(center.x + base2 / 2, center.y + _height / 2));	//Upper Right
		points.push_back(Point(center.x, center.y - _height / 2));	//Lower center
		points.push_back(Point(center.x - base1 / 2, center.y - _height / 2));	//Lower Left
		points.push_back(Point(center.x + base1 / 2, center.y - _height / 2));	//Lower Right
	}
	void zoom(double n);
	void printOUT(ostream& out);
};
