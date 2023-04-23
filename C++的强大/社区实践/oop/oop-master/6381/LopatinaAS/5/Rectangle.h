#pragma once

#include "Shape.h"
#include <ostream>

class Rectangle : public Shape {
public:
	Rectangle(double x, double y, unsigned int width, unsigned int  height, std::string color_sh);
	void move(double x_new, double y_new) override;
	void rotation(double angle) override;
	void scaling(double k) override;
	int perimetr() override;
	void print () const override;
private:
	unsigned int height;
	unsigned int width;
};
