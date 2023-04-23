#pragma once
#include "shape.h"

class RightTriangle : public Triangle
{
public:

	RightTriangle() :Triangle()
	{

	}


	RightTriangle(std::vector<Point> array) :Triangle(array) {

		double  maxSide = side[0];
		//проверка на свойства прямоугольного треугольника
		//Поиск гипотинузы .Далее проверка Т Пифагора
		
		std::nth_element(side.begin(), side.begin(), side.end(), std::greater<double>());
		double  hyp = sqrt(pow(side[1], 2.0) + pow(side[2], 2.0));
		if (side[0] != hyp)
			throw std::invalid_argument("T.Pifagor wrong");

		colour_ = 0;

		Point_ = array;
		ID_ = setNextID();

	}


	void showShape(std::ostream &os) const  override
	{
		os << "I'm Right Triangle" << std::endl;
		for (size_t i = 0; i<pointCount_; ++i) {

			os << "POINT " << i + 1 << "(" << Point_[i].getX() << ";" << Point_[i].getY() << ")" << std::endl;
		}

	}

};