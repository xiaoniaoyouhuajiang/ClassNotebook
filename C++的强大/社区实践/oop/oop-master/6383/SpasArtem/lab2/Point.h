#pragma once
#include <iostream>
using namespace std;

class Point {
private:
	double x;
	double y;
public:
	Point(double x, double y);
	Point() {};
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
};