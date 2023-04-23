#pragma once
#include "stdafx.h"
#include "Shape.h"
class Ellips : public Shape {
public:
	int  SmallAxle, BigAxle;
	int Id;
	Ellips(int, int, int, int, double, int, string);
	Ellips(int, int);
	int GetSAxle();
	int GetBAxle();
	void SetAxles(int, int);
	friend ostream&operator<<(ostream&a, const Ellips&b) {

		a << "ID фигуры: id=" << b.Id << "\n";
		a << "Центр фигуры: x=" << b.X << "; y=" << b.Y << "\n";
		a << "Цвет: " << b.Color << "\n";
		a << "Угол поворота фигуры: fi=" << b.Angle << "\n";
		a << "Масштаб: delta=" << b.Scale << "\n";
		a << "Высота эллипса с учётом масштабирования=" << b.BigAxle*b.Scale << "  Ширина эллипса=" << b.SmallAxle*b.Scale << "\n";
		return a;
	}
	~Ellips();
};