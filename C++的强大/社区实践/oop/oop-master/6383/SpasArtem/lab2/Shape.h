#pragma once
#include <string>
#include "Point.h"
#include <vector>

class Shape {

public:
	Shape(){};
	virtual ~Shape() {};
	virtual void scale(double k) = 0;
	void move(double new_x, double new_y);
	void turn(double angle);
protected:
	string color;
	Point centre;
	vector <Point> vertex;
};


