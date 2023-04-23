#pragma once
#include "Ellipse.h"

class SectorEllipse : public Ellipse {
private:
	double R1;//длина первого радиуса
	double R2;//длина второго радиуса
	double Angle1;//угол между первой стороной сектора и осью ОХ
	double Angle2;//угол между второй стороной сектора и осью ОХ
public:
	SectorEllipse();
	SectorEllipse(double, double, double, double, double, double);
	SectorEllipse(double, double, double, double, double, double, std::string);
	~SectorEllipse();
	friend std::ostream & operator << (std::ostream&os, const SectorEllipse& a) { //оператор вывода в поток вывода
		os << "-------------------------------------------" << std::endl;
		os << "Figure: Sector Of Ellipse" << std::endl;
		os << "ID: " << a.ID << std::endl;
		os << "Colour: " << a.getColour() << std::endl;
		os << "Coordinates of the center: (" << a.X0 << "," << a.Y0 << ")" << std::endl;
		os << "First diagonal: " << a.R1 << std::endl;
		os << "Second diagonal: " << a.R2 << std::endl;
		os << "Angle between the x-axis and the first side: " << a.Angle1 << std::endl;
		os << "Angle between the x-axis and the second side: " << a.Angle2 << std::endl;
		os << "Angle of rotation: " << a.Angle << std::endl;
		os << "-------------------------------------------" << std::endl;
		return os;
	}
};