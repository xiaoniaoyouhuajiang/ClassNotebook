#pragma once
#include "Circle.h"

class Curve : public Circle{
	private:
		double Angle1; //угол между первой стороной дуги и осью ОХ
		double Angle2; //угол между второй стороной дуги и осью ОХ
	public:
		Curve(double, double, double, double, double);
		Curve(double, double, double, double, double, std::string);
		~Curve();
		void print(std::ostream &) const;
};
