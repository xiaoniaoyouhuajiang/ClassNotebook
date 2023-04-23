#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <string>

class Shape
{
	public:
		double X0;
		double Y0;//координаты центра
		std::string Colour; //цвет
		int NUMBER; //номер фигуры
		double Angle; //угол поворота в градусах
		static int number; //счётчик
		Shape();
		virtual ~Shape(){}
		void Movement(double, double); //перемещение
		void Rotation(double); //вращение
		virtual void Scaling(double) = 0; //масштабирование 
		void setColour(std::string); //установка цвета
		std::string getColour() const; //получение цвета
		virtual void print(std::ostream &) const = 0;
		friend std::ostream& operator << (std::ostream &, const Shape &);
};

#endif