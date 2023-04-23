#include "ellipse.h"

ellipse::ellipse(int small_ax, int big_ax, paint_area_info paint_info) : shape(paint_info)
{
	small_axle = float(small_ax);
	big_axle = float(big_ax);

	cur_angle = 0;
	cur_ratio = 0.0f;
	X = Y = 0;
	this->type = "ellipse";
}

void ellipse::redraw()
{
	small_axle = small_axle * (1 + cur_ratio);
	big_axle = big_axle * (1 + cur_ratio);
	p_info.x_center+=X;
	p_info.y_center-=Y;

	float sa2 = (float)(small_axle * small_axle);
	float ba2 = (float)(big_axle * big_axle);
	float discr = 0.0f;
	int v_x = int(p_info.x_center - big_axle), v_y = int(p_info.y_center);
	int n_x = int(p_info.x_center - big_axle), n_y = int(p_info.y_center);

	int new_x, new_y;

	HPEN hPen;
	hPen = CreatePen(PS_DASH, 1, RGB(p_info.color.r , p_info.color.g,
		             p_info.color.b));
	SelectObject(p_info.area_ptr, hPen);

	for(int x = int(p_info.x_center - big_axle); x <= int(p_info.x_center + big_axle); x++)
	{
		discr = sqrt(sa2 * (1 - (x - p_info.x_center) * (x - p_info.x_center) / ba2));

		math_rotate(p_info.x_center, p_info.y_center, v_x, v_y, cur_angle, new_x, new_y); 
		MoveToEx(p_info.area_ptr, new_x, new_y, NULL);

		math_rotate(p_info.x_center, p_info.y_center, x, p_info.y_center + (int)discr, cur_angle, new_x, new_y); 
		LineTo(p_info.area_ptr, new_x, new_y);

		v_x = x;
		v_y = p_info.y_center + (int)discr;

		math_rotate(p_info.x_center, p_info.y_center, n_x, n_y, cur_angle, new_x, new_y);
		MoveToEx(p_info.area_ptr, new_x, new_y, NULL);

		math_rotate(p_info.x_center, p_info.y_center, x, p_info.y_center - (int)discr, cur_angle, new_x, new_y);
		LineTo(p_info.area_ptr, new_x, new_y);
		n_x = x;
		n_y = p_info.y_center - (int)discr;
	}
}

void ellipse::setXY(int x, int y)
{
	X = x;
	Y = y;
}

int ellipse::getX()
{
	return this->X;
}

int ellipse::getY()
{
	return this->Y;
}

void ellipse::draw(int x1, int y1)
{
	X = x1;
	Y = y1;
	redraw();
}

void ellipse::rotate(int angle)
{
	cur_angle = angle_mod(angle);
}

void ellipse::scale(float ratio)
{
	cur_ratio = ratio;
}

void ellipse::set_big_axle(int ba)
{
	big_axle = float(ba);
}

int ellipse::get_big_axle()
{
	return int(this->big_axle);
}

void ellipse::set_small_axle(int ba)
{
	small_axle = float(ba);
}

int ellipse::get_small_axle()
{
	return int(this->small_axle);
}

double ellipse::perimetr()
{
	return double(PI*(this->small_axle + this->big_axle));
}

std::ostream& operator<<(std::ostream& os, ellipse& el1)
{
	os << "===ЭЛЛИПС===\n" << el1.getX() << ";" << el1.getY() << "\nМаленькая дуга: " << el1.get_small_axle() << "\nБольшая дуга: " << el1.get_big_axle() << "\nПериметр: " << el1.perimetr();

	return os;
}