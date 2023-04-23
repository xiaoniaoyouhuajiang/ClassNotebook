#pragma once
#include <Windows.h>
#include <iostream>

struct rgb_color
{
	unsigned char r, g, b;
	rgb_color(int tr, int tg, int tb)
	{
		r = tr;
		g = tg;
		b = tb;
	}
	rgb_color()
	{
		r = g = b = 0;
	}
};

struct paint_area_info
{
	int area_height;
	int area_width;

	int x_center;
	int y_center;

	HDC area_ptr;
	rgb_color color;

	paint_area_info(int ah, int aw, int x_c, int y_c, HDC & ap, rgb_color col)
	{
		area_height = ah;
		area_width = aw;
		
		x_center = x_c;
		y_center = y_c;

		area_ptr = ap;
		color = col;
	};

	paint_area_info()
	{
	}
};

class shape
{
protected:
	paint_area_info p_info;
	
	std::string type;

	int cur_angle;
	float cur_ratio;

	virtual void redraw() = 0;
	void math_rotate(int x0, int y0, int x, int y, int angle, int & new_x, int & new_y);
public:
	shape(paint_area_info paint_info);
	virtual ~shape(){}
	float PI;

	int angle_mod(float n);
	std::string shape_type();

	void set_color(rgb_color new_color);
	rgb_color get_color();
	static int comparePerimeter(shape&, shape&);

	virtual void rotate(int angle) = 0;
	virtual void scale(float ratio) = 0;

	virtual double perimetr() = 0;
};