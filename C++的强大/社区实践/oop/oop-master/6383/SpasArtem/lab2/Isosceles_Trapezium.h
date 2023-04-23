#pragma once
#include "Shape.h"

class Isosceles_Trapezium : public Shape {
public:
	//Isosceles_Trapezium(double x, double y, double height, double length_bot, double length_top, string color);
	Isosceles_Trapezium(){};
	Isosceles_Trapezium(double x, double y, double delta, double height, double length_bot, double length_top, double edge, string color);
	virtual void scale(double k);
	virtual ~Isosceles_Trapezium() {};
	//double get_edge();
	//void set_edge(double edge);
	friend ostream& operator << (ostream &out, Isosceles_Trapezium &is_tr);	
protected:
	double height;
	double length_bot;
	double length_top;
	double delta;
	double edge;
};