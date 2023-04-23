#pragma once
#include "Shape.h"

class Ellipse :public Shape
{
private:
	double R1;//длина первого радиуса
	double R2;//длина второго радиуса
public:
	Ellipse();
	Ellipse(double, double, double, double);
	Ellipse(double, double, double, double, std::string);
	void Scaling(double) override;;//масштабирование 
	~Ellipse();
	friend std::ostream & operator << (std::ostream&os, const Ellipse& a) { //оператор вывода в поток вывода
		os << "-------------------------------------------" << std::endl;
		os << "Figure: Ellipse" << std::endl;
		os << "ID: " << a.ID << std::endl;
		os << "Colour: " << a.getColour() << std::endl;
		os << "Coordinates of the center: (" << a.X0 << "," << a.Y0 << ")" << std::endl;
		os << "First diagonal: " << a.R1 << std::endl;
		os << "Second diagonal: " << a.R2 << std::endl;
		os << "Angle of rotation: " << a.Angle << std::endl;
		os << "-------------------------------------------" << std::endl;
		return os;
	}
};