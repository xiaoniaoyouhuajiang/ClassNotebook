#include <math.h>
#include "shape.h"

void shape::set_color(rgb_color new_color)
{
	p_info.color = new_color;
};

rgb_color shape::get_color()
{
	return p_info.color;
}

shape::shape(paint_area_info paint_info)
{
	PI = 3.1415;
	p_info = paint_info;
};

void shape::math_rotate(int x0, int y0, int x, int y, int angle, int & new_x, int & new_y)
{
	float theta = (float)angle * PI / 180.0f;
	new_x = (int)((float)(x - x0) * cos(theta) - (float)(y - y0) * sin(theta)) + x0;
	new_y = (int)((float)(x - x0) * sin(theta) + (float)(y - y0) * cos(theta)) + y0;
}

int shape::comparePerimeter(shape& first, shape& second)
{
	if(first.perimetr() == second.perimetr()){
		return 0;
	}else if(first.perimetr() > second.perimetr()){
		return 1;
	}else{
		return -1;
	}
}

int shape::angle_mod(float n){
	n = abs(n);
	while(n >= 360)
		n-=360;
	return int(n);
}

std::string shape::shape_type(){
	return this->type;
}