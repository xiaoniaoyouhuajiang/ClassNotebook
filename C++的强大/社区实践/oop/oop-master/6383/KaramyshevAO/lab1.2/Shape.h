#pragma once
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;
struct Point {
	double x;
	double y;
	Point(double inpx, double inpy) : x(inpx), y(inpy) {}
	Point(const Point& CopyPoint) : x(CopyPoint.x), y(CopyPoint.y) {}
	Point() {}
};

struct Color {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	Color(unsigned int red, unsigned int green, unsigned int blue) : red(red), green(green), blue(blue) {}
	Color(const Color& CopyColor) : red(CopyColor.red), green(CopyColor.green), blue(CopyColor.blue) {}
	Color() {}
};

class Shape {
	int ID;
	static int next_ID;
protected:
	Point cntr;
	Color clr;
	Shape(Point cntr, Color clr);
public:
	const Color& Get_Color() const;
	const Point& Get_Point() const ;
	const int Get_ID() const;

	virtual void Calibr(double calibr) = 0;
	virtual void Grad(double grad) = 0;
	virtual void Move(double x, double y) = 0;
	friend ostream& operator <<(ostream &os, const Shape &c);
};
