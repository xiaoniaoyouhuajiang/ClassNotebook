#pragma once
#include "triangle.h"

class IsoscelesTriangle : public Triangle
{
public:
	~IsoscelesTriangle();
	IsoscelesTriangle(const Point & top, double angle, double side);
	IsoscelesTriangle(const Point & top, double angle, double side,  std::string red, std::string green, std::string blue);
	IsoscelesTriangle(const IsoscelesTriangle & other);
	bool isItNotIsoscelesTriangle() const;
	void scale(double coef = 1);
	void rotate(double angle = 0);							
	void move(const Point & p);
	void try_catch_isosceles_triangle();
private:
	void out(std::ostream & out_) const override;
	double angle;
};