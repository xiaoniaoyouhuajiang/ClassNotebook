#pragma once
#include "Shape.h"

class Circle : public Shape {
protected:
	double radius;
public:
	Circle(double input_radius, Point &cntr, Color &clr);
	const double Get_Radius()const;
	virtual void Calibr(double calibr) override;
	virtual void Grad(double grad) override {};
	virtual void Move(double x, double y) override;
	friend ostream& operator <<(ostream &os, const Circle &c);
};
