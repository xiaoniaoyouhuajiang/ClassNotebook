
#include "rectangle.h"
#include <string>
#include <locale>
#include "shape.h"
#include <iostream>

using namespace std;


Rectangle::Rectangle(Point current_center, int angle, double scale, double width, double height) :
	Shape(current_center, angle, scale),
	width(width),
	height(height)
{
	vertex.resize(4);

	vertex[0].x = vertex[1].x = current_center.x - width / 2;
	vertex[2].x = vertex[3].x = current_center.x + width / 2;
	vertex[0].y = vertex[2].y = current_center.y + height / 2;
	vertex[3].y = vertex[1].y = current_center.y - height / 2;

	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("Negative width and height!?!");
	}
}


void Rectangle::print(ostream &ost)
{
	setlocale(LC_ALL, "Rus");
	ost << endl << "Rectangle" << endl;
	ost << endl << "Coordinates: " <<
		"(" << vertex[1].x << ";" << vertex[1].y << ")" <<
		"(" << vertex[0].x << ";" << vertex[0].y << ")" <<
		"(" << vertex[2].x << ";" << vertex[2].y << ")" <<
		"(" << vertex[3].x << ";" << vertex[3].y << ")" << endl;
	ost << endl << "Angle: " << angle << endl;
	color_type temp = get_color();
	ost << endl << "Color: " << temp << endl << endl;
}

void Rectangle::move(Point new_center)
{
	current_center.x = new_center.x;
	current_center.y = new_center.y;
	vertex[0].x = vertex[1].x = new_center.x - width / 2;
	vertex[2].x = vertex[3].x = new_center.x + width / 2;
	vertex[0].y = vertex[2].y = new_center.y + height / 2;
	vertex[3].y = vertex[1].y = new_center.y - height / 2;
}

void Rectangle::Scale(double scale) 
{
	width *= scale;
	height *= scale;
	vertex[0].x = vertex[1].x = current_center.x - width / 2;
	vertex[2].x = vertex[3].x = current_center.x + width / 2;
	vertex[0].y = vertex[2].y = current_center.y + height / 2;
	vertex[3].y = vertex[1].y = current_center.y - height / 2;
}
void Rectangle::rotate(int new_angle)
{
	double angle = new_angle * 3.14 / 180;
	Point temp_left_top;
	Point temp_left_bottom;
	Point temp_right_top;
	Point temp_right_bottom;
	temp_left_top.x = vertex[1].x;
	temp_left_bottom.x = vertex[0].x;
	temp_right_top.x = vertex[3].x;
	temp_right_bottom.x = vertex[2].x;
	temp_left_top.y = vertex[1].y;
	temp_left_bottom.y = vertex[0].y;
	temp_right_top.y = vertex[3].y;
	temp_right_bottom.y = vertex[2].y;

	vertex[1].x = current_center.x + (temp_left_top.x - current_center.x) * cos(angle) - (temp_left_top.y - current_center.y) * sin(angle);
	vertex[1].y = current_center.y + (temp_left_top.x - current_center.x) * sin(angle) + (temp_left_top.y - current_center.y) * cos(angle);
	vertex[3].x = current_center.x + (temp_right_top.x - current_center.x) * cos(angle) - (temp_right_top.y - current_center.y) * sin(angle);
	vertex[3].y = current_center.y + (temp_right_top.x - current_center.x) * sin(angle) + (temp_right_top.y - current_center.y) * cos(angle);
	vertex[0].x = current_center.x + (temp_left_bottom.x - current_center.x) * cos(angle) - (temp_left_bottom.y - current_center.y) * sin(angle);
	vertex[0].y = current_center.y + (temp_left_bottom.x - current_center.x) * sin(angle) + (temp_left_bottom.y - current_center.y) * cos(angle);
	vertex[2].x = current_center.x + (temp_right_bottom.x - current_center.x) * cos(angle) - (temp_right_bottom.y - current_center.y) * sin(angle);
	vertex[2].y = current_center.y + (temp_right_bottom.x - current_center.x) * sin(angle) + (temp_right_bottom.y - current_center.y) * cos(angle);
	angle += new_angle;

}
