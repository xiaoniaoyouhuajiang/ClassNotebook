#pragma once
#include "Rectangle.h"

void Rectangle::zoom(double n) {
	prepare_for_zoom(n);
	sideA *= n;
	sideB *= n;
}

void Rectangle::printOUT(ostream& out) {
	out << "Создан прямоугольник" << endl;
	out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
	out << "Длины сторон: " << sideA << " , " << sideB << endl;
	out << "Точки прямоугольника:" << endl;
	for (const auto& i : points) {
		out << "(" << i.x << ", " << i.y << ")\n";
	}
	out << "Цвет: " << color << endl;
	out << "Угол: " << angle << endl;
}