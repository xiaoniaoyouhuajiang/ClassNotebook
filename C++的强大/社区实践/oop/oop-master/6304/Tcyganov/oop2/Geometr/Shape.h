#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include "Point.h"

class Shape
{
protected:
	Point p1;
	Point p2;
	virtual Point getCenter();
	std::string color;
	float toRadian(int degree);
public:
	virtual void MoveTo(float x, float y) {}
	virtual void Rotate(int angle);
	virtual void Scale(float value) {}
	virtual std::string getColor() { return this->color; }
	virtual void setColor(std::string color) { }
	
	Shape(Point p1, Point p2);
	~Shape();
};

