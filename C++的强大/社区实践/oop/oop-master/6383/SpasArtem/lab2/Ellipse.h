#pragma once
#include "Shape.h"
using namespace std;


class Ellipse : public Shape {
protected:
	double rad1;
	double rad2;
	Point centre;
	string color;
public:
	Ellipse(double x, double y, int rad1, int rad2, string color);
	~Ellipse() {};
	void scale(double k);
	friend ostream& operator << (ostream &out, Ellipse &el);
};
