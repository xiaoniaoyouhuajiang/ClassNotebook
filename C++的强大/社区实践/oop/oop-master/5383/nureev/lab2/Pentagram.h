#pragma once

#include "figure.h"

#include "point.h"



class Pentagram : public Figure

{

private:

	double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0, x4 = 0.0, y4 = 0.0, x5 = 0.0, y5 = 0.0;


protected:
	double lenght1, lenght2, lenght3, lenght4, lenght5;
	Point A, B, C, D, E, Center;
	

public:

	Pentagram(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5);

	Pentagram(){}

	double distance(int x, int y);

	void set_length(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5);


	void scale(double num);

	void turn(double angle);

	void sdvig(double num1, double num2);

	//void info();

	void print(std::ostream &os) override;


};