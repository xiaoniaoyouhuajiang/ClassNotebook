#pragma once
#ifndef PENTAGON_H
#define PENTAGON_H
#include "shape.h"
#include "point.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Pentagon : public Shape {

public:
	Pentagon(Point current_center, int angle, double scale, vector <Point> vertex);
	void Pentagon::move(Point new_center) override;
	virtual void Scale(double scale) override;
	void print(ostream &ost) override;
	void rotate(int new_center) override;
};
#endif