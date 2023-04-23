#pragma once
#include "Circle.h"

class Arc : public Circle {
	Point P1;
	Point P2;
public:
	Arc(Point p1, Point p2, double input_radius, Point &cntr, Color &clr);
	const Point& Get_P1() const;
	const Point& Get_P2() const;
	void Calibr(double calibr) override;
	void Grad(double grad) override ;
	void Move(double x, double y) override;
	friend ostream& operator <<(ostream &os, const Arc &c);
};
