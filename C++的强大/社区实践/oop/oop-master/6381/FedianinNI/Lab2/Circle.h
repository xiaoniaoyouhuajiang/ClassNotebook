#pragma once
#include "Shape.h"

class Circle :public Shape
{
	protected:
		double R; //длина радиуса
	public:
		Circle();
		Circle(double, double, double);
		Circle(double, double, double, std::string);
		~Circle();
		void Scaling(double) override;
		void print(std::ostream &) const;
};
