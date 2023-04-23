
#include "Square.h"


void Square::scale(int k)
{
	side *= k;
	zoom(k);
}

void Square::printOUT(std::ostream& out) {
	out << "Квадрат!" << std::endl;
	out << "Координаты центра: (" << center.getX() << ", " << center.getY() << ")" << std::endl;
	out << "Длина стороны квадрата: " << side << std::endl;
	out << "Точки квадрата:" << std::endl;
	for (int i = 0; i < points.size(); i++)
	{
		out << "(" << points[i].getX() << ", " << points[i].getY() << ")\n";
	}
	out << "Цвет: " << color << std::endl;
	out << "Угол: " << angle << std::endl;

}
