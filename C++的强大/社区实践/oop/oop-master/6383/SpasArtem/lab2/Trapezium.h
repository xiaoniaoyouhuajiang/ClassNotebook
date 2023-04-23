#pragma once
#include "Isosceles_Trapezium.h"

class Trapezium : public Isosceles_Trapezium {
public:
	Trapezium(double x, double y, double delta, double height, double length_bot, double length_top, double edge, string color, double edge_2);
	~Trapezium() {};
	void scale(double k);
	friend ostream& operator << (ostream &out, Trapezium &tr);

protected:
	double edge_2;
	/*double height;
	double length_bot;
	double length_top;
	double delta;*/
};