#pragma once
#include "Shape.hpp"
#include <iostream>

class Circle : public Shape
{
public:
	Circle(double R = 0) : R(R)
	{ }
	double getRadius() const;
	void setRadius(double newR);
	void scale(double sc) override;
	void print() const override;
private:
	double R;
};
