#pragma once
#include "Shape.h"

class Parallelogram :public Shape
{
private:
	double D1;//длина первой диагонали
	double D2;//длина второй диагонали
	double AngleBetweenDiagonal;
public:
	Parallelogram();
	Parallelogram(double, double, double, double, double);
	Parallelogram(double, double, double, double, double, std::string);
	void Scaling(double) override;//масштабирование 
	~Parallelogram();
	friend std::ostream & operator << (std::ostream&os, const Parallelogram& a) { //оператор вывода в поток вывода
		os << "-------------------------------------------" << std::endl;
		os << "Figure: Parallelogram" << std::endl;
		os << "ID: " << a.ID << std::endl;
		os << "Colour: " << a.getColour() << std::endl;
		os << "Coordinates of the center: (" << a.X0 << "," << a.Y0 << ")" << std::endl;
		os << "First diagonal: " << a.D1 << std::endl;
		os << "Second diagonal: " << a.D2 << std::endl;
		os << "Angle between the diagonals: " << a.AngleBetweenDiagonal << std::endl;
		os << "Angle of rotation: " << a.Angle << std::endl;
		os << "-------------------------------------------" << std::endl;
		return os;
	}
};