#include <cmath>
#include "Dot.h"


Dot::Dot() :x(0), y(0) {} //конструктор по умолчанию

Dot::Dot(double _x, double _y) : x(_x), y(_y) {} //конструктор со списом инициализации

double Dot::distance(const Dot &smth) const // подсчет расстояния
{
	double dx = smth.x - x;
	double dy = smth.y - y;
	return sqrt(dx*dx + dy*dy);
}

void Dot::rotate(double angle) // поворот
{
	double old_x = x;
	double old_y = y;

	x = old_x * cos(angle) - old_y * sin(angle);
	y = old_x * sin(angle) + old_y * cos(angle);
}
bool Dot::operator == (const Dot &smth) const {
	return (this->x == smth.x && this->y == smth.y);
}

bool Dot::operator != (const Dot &smth) const {
	return !(*this == smth);
}
