#pragma once
#include "Shape.h"

class Ellipse : public Shape {
	Point F1;
	Point F2;
	double a;
public:
	Ellipse(Point f1, Point f2, double input_a, Point &cntr, Color &clr);
	const double Get_a()const;
	const Point& Get_F1()const;
	const Point& Get_F2()const;
	const double Get_c()const;
	void Calibr(double calibr) override;
	void Grad(double grad) override;
	void Move(double x, double y) override;
	friend ostream& operator <<(ostream &os, const Ellipse &c);
};
