#pragma once
#include <math.h>
#include "shape.h"
#include <iostream>

class ellipse : public shape
{
private:
	int X, Y;

	float small_axle;
	float big_axle;

	void redraw();

public:
	ellipse(int small_ax, int big_ax, paint_area_info paint_info);
	virtual ~ellipse(){}

	void setXY(int x, int y);
	int getX();
	int getY();

	void set_big_axle(int ba);
	int get_big_axle();

	void set_small_axle(int ba);
	int get_small_axle();
	
	void draw(int x1 = 0, int y1 = 0);
	void rotate(int angle);
	void scale(float ratio);

	double perimetr();

	friend std::ostream& operator<<(std::ostream& os, ellipse& el1);
};

