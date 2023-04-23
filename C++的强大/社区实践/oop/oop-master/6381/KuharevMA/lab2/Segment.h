#pragma once
#include "stdafx.h"
#include "Shape.h"
using namespace std;

class Segment : public Shape
{
private:
	double Length;
	int Id;
public:
	Segment(int, int, int, double, int, string);
	Segment(int Length);
	void SetLength(int);
	int GetLength();
	friend ostream&operator<<(ostream&a, const Segment&b) {
		a << "ID фигуры: id=" << b.Id << "\n";
		a << "Центр фигуры: x=" << b.X << "; y=" << b.Y << "\n";
		a << "Цвет: " << b.Color << "\n";
		a << "Угол поворота фигуры: fi=" << b.Angle << "\n";
		a << "Масштаб: delta=" << b.Scale << "\n";
		a << "Длина с учетом мастаба: Горизонтальная сторона=" << b.Length*b.Scale << "\n";
		return a;
	}
	~Segment();
};