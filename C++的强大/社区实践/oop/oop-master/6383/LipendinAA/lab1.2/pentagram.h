#pragma once
#ifndef PENTAGRAM_H
#define PENTAGRAM_H
#include "shape.h"
#include "point.h"
#include <string>
#include "pentagon.h"
#include <iostream>

using namespace std;

class Pentagram :public Shape {
private:
	int pentagramAngle = 0;
	double radius;

public:
	Pentagram(Point current_center, int angle, double scale, double radius);
	void Scale(double scale) override;
	void move(Point new_center) override;
	void print(ostream &ost) override;
	void rotate(int NewAngle) override;
};


#endif