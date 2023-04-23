#pragma once
#include "shape.h"
#include <iostream>

class circle : public shape
{
private:
	int X, Y;

	int radius;
	void redraw();
	
public:
	circle(int rad, paint_area_info paint_info);
	virtual ~circle(){}

	void setXY(int x, int y);
	int getX();
	int getY();

	int get_radius();
	void set_radius(int r);
	
	void draw(int x1 = 0, int y1 = 0);
	void rotate(int angle);
	void scale(float ratio);

	double perimetr();

	friend std::ostream& operator<<(std::ostream& os, circle& c1);
};

