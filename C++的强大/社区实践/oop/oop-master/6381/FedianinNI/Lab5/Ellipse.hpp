#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "Shape.hpp"

class Ellipse :public Shape
{
	private:
		double R1;//длина первого радиуса
		double R2;//длина второго радиуса
	public:
		Ellipse(double, double, double, double);
		Ellipse(double, double, double, double, std::string);
		//~Ellipse();
		void Scaling(double) override; 
		void print(std::ostream &) const;
};

#endif