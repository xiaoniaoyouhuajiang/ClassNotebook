#pragma once

class Point
{
public:
	double x;
	double y;

	Point(); //Дефолтный констуктор

	Point(double x0, double y0); //Установить точки пользователя

	void ShowPoint(); // Показать точки
};
