#pragma once
#include "Shape.h"

class Isosceles_triangle: public Shape{
	double save_side;
	double angle_between_save;
public:
	Isosceles_triangle(double, double, double, double);
	Isosceles_triangle(double, double, double, double, std::string);
	~Isosceles_triangle();
	double square();
	void scaling(double);
	void print(std::ostream &) const;
};