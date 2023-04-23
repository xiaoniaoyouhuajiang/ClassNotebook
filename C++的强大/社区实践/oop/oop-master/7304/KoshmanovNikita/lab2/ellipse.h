#include "shape.h"

#ifndef ELLIPSE_H
#define ELLIPSE_H


class Ellipse : public Shape
{
	double a;
	double b;
	double angle;
	void set_crd();

public:
	Ellipse(double, double, Point, double = 0);
	void move(Point);
	void rotate(double);
	void scale(double);
	void print(std::ostream&);
	~Ellipse();
};

#endif // ELLIPSE_H
