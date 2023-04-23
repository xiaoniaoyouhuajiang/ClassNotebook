#pragma once

#include <ostream>
#include "Shape.h"

class Trapezoid : public Shape {
public:
	Trapezoid(double shortX, double shortY, double longX, double longY, unsigned short_width, unsigned long_width, std::string color_sh);
	void move(double x_new, double y_new) override;
	void rotation(double angle) override;
	void scaling(double k) override;
	int perimetr() override;
	void setCentre(double x, double y);
	Dot* getCentre();
	void centreMove(double x, double y);
	void print () const override;
private:
	unsigned int height;
	Dot* centre = nullptr;
};

