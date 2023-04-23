#pragma once
#include "shape.h"


//Класс окружность
class Circum : public Shape
{
private:
	//Радиус окружности
	double radius;


public:
	//Конструктор
	Circum(double radius, Point &centrum, Color &color);

	//Узнать радиус окружности
	double Get_Rad() const;

	//Переопределения виртуальных функций
	virtual void Scale(double scale)		override;		//масштабирование
	virtual void Move( double x, double y)	override;		//перемещение

	virtual void Rotate( double angle)	  override{};		//вращение (окружность не вращается)				
};

// Вывод в поток информации о окружности
std::ostream &operator <<(std::ostream &out, const Circum &circum);