#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"
#include "point.h"
#include <string>
#include <iostream>
#include "pentagon.h"

using namespace std;

class Rectangle : public Shape {
protected:
	double width;
	double height;

public:
	Rectangle(Point current_center, int angle, double scale, double width, double height);
	void Scale(double scale) override;
	void move(Point new_center) override;
	void print(ostream &ost) override;
	void rotate(int NewAngle) override;

};


#endif