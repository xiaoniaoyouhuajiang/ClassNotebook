#pragma once

#include "Shape.h"
#include <ostream>

class Circle : public Shape {
public:
	Circle(unsigned radius, Dot* center, std::string color_sh);
	void move(double x_new, double y_new) override;
	void rotation(double angle) override;
	void scaling(double k) override;
	int perimetr() override;
	void set_angle(unsigned int angle);
	int get_angle();
	void print () const override;
private:
	unsigned int radius;
	unsigned int angle;
};
