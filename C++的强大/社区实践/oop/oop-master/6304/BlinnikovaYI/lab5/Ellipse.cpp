#include "Ellipse.h"

void Ellipse::zoom(double n) {
	prepare_for_zoom(n);
	radiusX *= n;
	radiusY *= n;
}

void Ellipse::printOUT(ostream& out) {
	out << "Создан эллипс" << endl;
	out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
	out << "Длины радиусов: " << radiusX << " , " << radiusY << endl;
	out << "Точки эллипса:" << endl;
	for (const auto& i : points) {
		out << "(" << i.x << ", " << i.y << ")\n";
	}
	out << "Цвет: " << color << endl;
	out << "Угол: " << angle << endl;

}