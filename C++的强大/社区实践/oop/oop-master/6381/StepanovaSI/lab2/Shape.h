#pragma once
#include <iostream>
#include <string>

class Shape
{
	protected:
		std::string Colour;//цвет
		int ID;//идентификационный номер
		double Angle;//угол поворота в градусах
	public:
		static int id;
		Shape();
		~Shape();
		virtual void Movement(double, double)=0;//перемещение в указанные координаты
		void Rotation(double);//вращение на заданный угол
		virtual void Scaling(double)=0;//масштабирование 
		void setColour(std::string);//установка цвета
		std::string getColour() const;//получение цвета
};


