
#include "IsoscelesTriangle.h"


void isoscelesTriangle::scale(int k)
{

	side *= k;
	side2 *= k;
	zoom(k);
}
void isoscelesTriangle::printOUT(std::ostream& out) {
	out << "Равнобедренный треугольник!" << std::endl;
	out << "Координаты центра: (" << center.getX() << ", " << center.getY() << ")" << std::endl;
	out << "Длина сторон равнобедренного треугольника: " << side << " " << side2 << std::endl;
	out << "Угол равнобедренного треугольника: " << angleOfTriangle << std::endl;
	out << "Точки равнобедренного треугольника:" << std::endl;
	for (int i = 0; i < points.size(); i++)
	{
		out << "(" << points[i].getX() << ", " << points[i].getY() << ")\n";
	}
	out << "Цвет: " << color << std::endl;
	out << "Угол: " << angle << std::endl;

}
