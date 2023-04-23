#pragma once
#include "shape.h"
#include <vector>
#include <iostream>
#define PI 3.14159265359 

class Polygon : public Shape
{
public:
	Polygon();																						// конструктор по умолчанию
	Polygon(const std::vector<Point> tops);															// конструктор с параметрами
	Polygon(const std::vector<Point> tops, std::string red, std::string green, std::string blue);	// конструктор с параметрами
	Polygon(const Polygon & other);
	~Polygon() {}																					// деструктор
	Point find_center() const;										// находим центр
	void rotate(double angle = 0);									// поворот
	void scale(double coef = 1);									// масштабирование
	void move(const Point & p);										// сдвиг
	double to_radian(double angle);									// перевод в радианы
	void swap(Polygon & other);
protected:
	std::vector<Point> tops;										// определяем многоугольник по вершинам	
	void out(std::ostream & out_) const override;					// вывод информации о многоугольнике
};