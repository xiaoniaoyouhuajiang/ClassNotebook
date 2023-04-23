#pragma once
#include "Shape.h"

class Right_triangle: public Shape{
	double catheter_one;
	double catheter_two;
public:
	Right_triangle(double, double, double, double);
	Right_triangle(double, double, double, double, std::string);
	~Right_triangle();
	double square();
	void scaling(double);
	void print(std::ostream &) const;
};