#pragma once
#include <iostream>
#include "Dot.h"
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>

//чёрная магия для генерации случайных фигур (скопипащено)


struct Color {
	unsigned char R, G, B;
	Color(unsigned char _R = 0, unsigned char _G = 0, unsigned char _B = 0) : R(_R), G(_G), B(_B) {}
};

class Shape {
protected:
	std::vector<Dot> corners; //т.к все фигуры четырехугольники
	double angle;// угол

	static size_t counter;// кол-во фигур
	size_t id;//айди каждой фиугры

	Color color;//цвет


	virtual void print(std::ostream& OS) const = 0; // Вывод

public:
	Shape(std::vector<Dot> points, Color color, double angle) :
		id(counter++), angle(angle), color(color), corners(points) {} //консткруктор


	virtual ~Shape() {}//деструктор

	void move(Dot &new_center);//передвинуть
	void scale(double scale);//расстянуть
	void rotate(double new_angle);//повернуть

	Color get_color() const; //получить цвет
	void set_color(Color color);//установить цвет
	Dot get_center();//получить цвет
	size_t getId() const;//получить айди
	Dot& min_y(Dot& a, Dot& b) const;
	Dot& max_y(Dot& a, Dot& b) const;
	friend std::ostream& operator << (std::ostream& OS, const Shape& smth); // оператор вывода



									   //Задание
	bool common_side(Shape* other);

};


template <typename T>
bool float_comparison(T a, T b)
{
	if (!(std::isfinite(a) && std::isfinite(b))) { return a == b; }
	return std::fabs(a - b) <= std::numeric_limits<T>::epsilon() * std::max(std::fabs(a), std::fabs(b));
}

