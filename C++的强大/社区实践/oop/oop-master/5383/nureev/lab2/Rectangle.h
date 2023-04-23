#pragma once

#include "figure.h"

#include "point.h"
#include <string>


class Rectangle : public Figure

{

private:

	double width = 0.0, height = 0.0;

protected:

	Point A, B, C, D, Center;


public:

	Rectangle(int height, int width);

	Rectangle(){}

	double getWidth();

	double getHeight();

	void set_length(double width, double height);

	void scale(double num);

	void turn(double angle);

	void sdvig(double num1,double num2);

	//void info();

	double distance(int x, int y);

	void print(std::ostream &os) override;
	

};