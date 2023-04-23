#include <math.h>
#include "circle.h"

circle::circle(int rad, paint_area_info paint_info) : shape(paint_info)
{
	radius = rad;
	this->type = "circle";
}

void circle::redraw()
{
	radius = (int)((float)radius * (1.0f + cur_ratio));
	p_info.x_center+=X;
	p_info.y_center-=Y;

	float r2 = (float)(radius * radius);
	float discr = 0.0f;
	int v_x = p_info.x_center - radius, v_y = p_info.y_center;
	int n_x = p_info.x_center - radius, n_y = p_info.y_center;

	HPEN hPen;
	hPen = CreatePen(PS_DASH, 1, RGB(p_info.color.r , p_info.color.g,
		             p_info.color.b));
	SelectObject(p_info.area_ptr, hPen);

	for(int x = p_info.x_center - radius; x <= p_info.x_center + radius; x++)
	{
		discr = sqrt(r2 - (float)((x - p_info.x_center) * (x - p_info.x_center)));

		MoveToEx(p_info.area_ptr, v_x, v_y, NULL);
		LineTo(p_info.area_ptr, x, p_info.y_center + (int)discr);
		v_x = x;
		v_y = p_info.y_center + (int)discr;

		MoveToEx(p_info.area_ptr, n_x, n_y, NULL);
		LineTo(p_info.area_ptr, x, p_info.y_center - (int)discr);
		n_x = x;
		n_y = p_info.y_center - (int)discr;	
	}
}

void circle::setXY(int x, int y)
{
	X = x;
	Y = y;
}

int circle::getX()
{
	return this->X;
}

int circle::getY()
{
	return this->Y;
}

void circle::draw(int x1, int y1)
{
	X = x1;
	Y = y1;
	redraw();
}

void circle::rotate(int angle)
{
	cur_angle = angle_mod(angle);
}

void circle::scale(float ratio)
{
	cur_ratio = ratio;
}

int circle::get_radius()
{
	return radius;
}
void circle::set_radius(int r)
{
	radius = r;
}

double circle::perimetr()
{
	return double(2*PI*this->radius);
}

std::ostream& operator<<(std::ostream& os, circle& c1)
{
	os << "===ÎÊÐÓÆÍÎÑÒÜ===\n" << c1.getX() << ";" << c1.getY() << "\nÐàäèóñ: " << c1.get_radius() << "\nÏåðèìåòð: " << c1.perimetr();

	return os;
}