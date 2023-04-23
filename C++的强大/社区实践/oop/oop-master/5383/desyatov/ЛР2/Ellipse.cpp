#include "Ellipse.h"
#include <iostream>
using namespace std;

void Ellipse::ShowFigure()
{
	cout << "Координаты центра эллписа " << center.x << " " << center.y << endl;
}

Ellipse::Ellipse() //Стандартный конструктор
{
	type = "Эллипс";
	color = "Красный";
	center.x = 0;
	center.y = 0;
	scale = 0;
}

Ellipse::Ellipse(double l, double h)
{
	lenght = l;
	hight = h;
	rightEdge.x = center.x + l / 2;
	topEdge.y = center.y + h / 2;
	scale = 1;
	area = 3.14 * hight * lenght;
}

void Ellipse::Move(double x, double y)
{
	center.x = center.x + x;
	center.y = center.y + y;
	rightEdge.x = rightEdge.x + x;
	rightEdge.y = rightEdge.y + y;
}

Ellipse::~Ellipse()
{

}

void Ellipse::ChangeColor(string c)
{
	color = c;
	cout << "Цвет был изменен на " << c;
}

void Ellipse::SetPoints(double l, double h)
{
}

void Ellipse::ChangeAngle(double angle)
{
	double x0;

	x0 = rightEdge.x;
	rightEdge.x = rightEdge.x * cos(angle) - rightEdge.y * sin(angle);
	rightEdge.y = x0 * sin(angle) + rightEdge.y * cos(angle);

	x0 = topEdge.x;
	topEdge.x = topEdge.x * cos(angle) - topEdge.y * sin(angle);
	topEdge.y = x0 * sin(angle) + topEdge.y * cos(angle);
}

void Ellipse::print(ostream& output)
{
	output << "Тип фигуры - " << type << endl;
	output << "Цвет фигуры - " << color << endl;
	output << "Высота полуоси = " << hight << endl;
	output << "Длина  полуоси = " << lenght << endl;
	output << "Центр эллписа " << center.x << " " << center.y << endl;
	output << "Площадь эллипса = " << area << endl;
}

void Ellipse::ChangeScale(int n)
{
	hight = hight * n;
	lenght = lenght * n;
	rightEdge.x = lenght / 2;
	rightEdge.y = hight / 2;
	topEdge.y = hight / 2;
	topEdge.x = lenght / 2;
	scale = n;
	cout << "Масштаб был изменен на " << n << endl;
}

double Ellipse::getArea()
{
	area = 3.1415 * hight * lenght;
	return 0;
}

double Ellipse::compareAreas(Ellipse ell1, Ellipse ell2)
{
	if (ell1.area > ell2.area)
	{
		return 1;
		cout << "Площадь первой фигуры больше второй " << endl;
	}
	if (ell1.area < ell2.area)
	{
		return 2;
		cout << "Площадь первой фигуры меньше второй " << endl;
	}
	if (ell1.area == ell2.area)
	{
		return 3;
		cout << "Площади равны" << endl;
	}
}
/*
Название переменных ++
SetPoints реализация ++
длина ширина приватные ++
масштаб реализация ++
добавить конструкторы ++
Задание: найти площадь фигур, сравнить площадь двух фигур
За центр можно принять центр нижнего основания
*/