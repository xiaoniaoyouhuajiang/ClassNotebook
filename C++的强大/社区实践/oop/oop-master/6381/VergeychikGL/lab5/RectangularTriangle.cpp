
#include "RectangularTriangle.h"

void rectangularTriangle::scale(int k)
{
	side *= k;
	side2 *= k;
	zoom(k);
}
void rectangularTriangle::printOUT(std::ostream& out) {
	out << "Прямоугольный треугольник!" << std::endl;
	out << "Координаты центра: (" << center.getX() << ", " << center.getY() << ")" << std::endl;
	out << "Длина сторон прямоугольного треугольника: " << side << " " << side2 << std::endl;
	out << "Точки прямоугольного треугольника:" << std::endl;
	for (int i = 0; i < points.size(); i++)
	{
		out << "(" << points[i].getX() << ", " << points[i].getY() << ")\n";
	}
	out << "Цвет: " << color << std::endl;
	out << "Угол: " << angle << std::endl;
}
