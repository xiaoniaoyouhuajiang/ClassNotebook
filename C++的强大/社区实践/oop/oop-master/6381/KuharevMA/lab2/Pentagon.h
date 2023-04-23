#pragma once
#include "stdafx.h"
#include "Shape.h"
class Pentagon : public Shape {
public:
	int  Side;
	int Id;
	Pentagon(int, int, int, double, int, string);
	Pentagon(int);
	int GetSide();
	void SetSide(int);
	friend ostream&operator<<(ostream&a, const Pentagon&b) {
		a << "ID фигуры: id=" << b.Id << "\n";
		a << "Центр фигуры: x=" << b.X << "; y=" << b.Y << "\n";
		a << "Цвет: " << b.Color << "\n";
		a << "Угол поворота фигуры: fi=" << b.Angle << "\n";
		a << "Масштаб: delta=" << b.Scale << "\n";
		a << "Длины сторон с учетом мастаба: Сторона пятиугольника=" << b.Side*b.Scale << "\n";
		return a;
	}
	~Pentagon();
};