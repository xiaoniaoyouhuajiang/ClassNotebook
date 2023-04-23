#pragma once
#include "colour.h"
#include "center.h"
#include <algorithm>
#include <stdexcept>


class Shape 		// абстрактный класс
{
public:
	Shape();														// конструктор по умолчанию
	Shape(std::string red, std::string green, std::string blue);	// конструктор с параметром
	Shape(const Shape & other);										// конструктор копирования
	virtual ~Shape() {}												// виртуальный деструктор
	virtual	void move (const Point & p) = 0;						// перемещение фигуры 
	virtual void rotate (double angle = 0) = 0;						// поворот на указанный угол 
	virtual void scale (double coef = 1) = 0;						// масштабирование на указанный коэффициент
	Colour get_Colour() const; 										// получение цвета фигуры
	size_t get_ID() const;											// взятие ID фигуры
	size_t & get_ID();
	friend std::ostream & operator << (std::ostream & out_, const Shape & shape);	// оператор вывода в поток out
	
	virtual double area() const = 0;						// нахождение площади фигуры
	virtual double perimeter() const = 0;					// нахождение периметра фигуры
protected:
	virtual void out(std::ostream & out_) const = 0;							// вывод в поток
	static size_t count;														// задаем номер фигуры (увеличивается, когда создается новая фигура). Нужен для id
	size_t id;																	// id фигуры
	Colour colour;																// цвет фигуры
};
