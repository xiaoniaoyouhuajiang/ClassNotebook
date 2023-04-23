#pragma once
#include "Color.h"
#include "Point.h"
#include <vector>
#include <cmath>
#define pi 3.14159265

class Shape
{
protected:
	double angle;
	Point center;
	vector <Point> peaks;
	Color color;
public:
	static int id;
	Shape();
	Shape(Point , double, Color&);

	double getAngle() const;
	Color getColor() const;
	void setAngle(double);
	void setColor(Color&);

	virtual void move(Point);
	virtual void rotate(double);
	virtual void scale(double k) = 0;
	~Shape();
};

