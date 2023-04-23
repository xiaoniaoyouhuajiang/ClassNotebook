#pragma once
#include "shape.h"
#include <iostream>

class arc : public shape
{
private:
	int X, Y;

	float arc_radius;
	float arc_angle_start;
	float arc_angle_stop;

	void redraw();

public:
	arc(int r, int angle_start, int angle_end, paint_area_info paint_info);
	virtual ~arc(){}

	void setXY(int x, int y);
	int getX();
	int getY();

	int get_radius();
	int get_start_angle();
	int get_stop_angle();

	void set_radius(int r);
	void set_start_angle(int sa);
	void set_stop_angle(int sa);

	void draw(int x1 = 0, int y1 = 0);
	void rotate(int angle);
	void scale(float ratio);

	double perimetr();

	friend std::ostream& operator<<(std::ostream& os, arc& a1);
};

