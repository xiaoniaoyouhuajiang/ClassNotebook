
#include "Square.h"

void Square::zoom(double n) {
	prepare_for_zoom(n);
	side *= n;
}

void Square::printOUT(ostream& out) {
	out << "Создан квадрат" << endl;
	out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
	out << "Длина стороны квадрата: " << side << endl;
	out << "Точки квадрата:" << endl;
	for (const auto& i : points) {
		out << "(" << i.x << ", " << i.y << ")\n";
	}
	out << "Цвет: " << color << endl;
	out << "Угол: " << angle << endl;

}