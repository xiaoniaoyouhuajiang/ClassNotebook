#include "Shape.h"

Point Shape::getCenter() {
	return center;
}

void Shape::setColor(string color) {// установка цвета
	this->color = color;
}

void Shape::reLocate(double x, double y) {// перемещение в другие координаты (по центру)

	for (auto& i : points) {
		i.x += x - center.x;
		i.y += y - center.y;
	}
	center.x = x;
	center.y = y;
}

void Shape::prepare_for_zoom(double& n) {// масштабирование каждой точки
	if (n<0) {
		n = abs(n);
	}
	for (auto& i : points) {
		i.x *= n;
		i.y *= n;
	}
}

void Shape::turn(int angl) {// поворот на угол
	angl = angl % 360;
	angle += angl;
	double radian = angl*PI / 180;
	for (auto& i : points) {
		double x_ = i.x*cos(radian) - i.y*sin(radian);
		double y_ = i.y*cos(radian) + i.x*sin(radian);
		i.x = x_;
		i.y = y_;
	}
}