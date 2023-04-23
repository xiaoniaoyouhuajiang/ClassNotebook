#pragma once
#include "triangle.h"

class RightTriangle : public Triangle
{
public:
	RightTriangle(const Point & top, const double catheter_1, const double catheter_2);
	RightTriangle(const Point & top,  const double catheter_1, const double catheter_2, std::string red, std::string green, std::string blue);
	RightTriangle(const RightTriangle & other);
	~RightTriangle();
	double area() const;
	bool isItNotRightTriangle() const;
	void scale(double coef = 1);
	void rotate(double angle = 0);							
	void move(const Point & p);
	void try_catch_right_triangle();
private:
	void out(std::ostream & out_) const override;
};