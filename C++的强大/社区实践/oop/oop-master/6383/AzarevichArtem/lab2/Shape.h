#pragma once

#include <iostream>
#include <cmath>


// Структура, отвечающая за цвет фигуры
struct Color
{
	char RED;
	char GREEN;
	char BLUE;

	Color(char R, char G, char B) :         RED(R),           GREEN(G),          BLUE(B) {}
	Color(    const Color &color) : RED(color.RED), GREEN(color.GREEN), BLUE(color.BLUE) {}
};

// Структура, являющая собой координаты точки в пространстве
struct Point
{
	double x;
	double y;

	Point( double x, double y) :   x(x),   y(y) {}
	Point(     const Point &p) : x(p.x), y(p.y) {}
	Point(){}
};

// Абстрактный класс "фигура"
class Shape
{
private:
	unsigned int ID;									// ID фигуры
	Color color;										// цвет фигуры

protected:
	
	Point centrum;										// центр фигуры
	

	// Конструктор
	Shape( Color &color, Point &centrum);

public:
	//Установить цвет
	void Set_Color(char R, char G, char B);				

	// Узнать значение полей:
	const Color & Get_Color() const;					// цвета фигуры
	const Point & Get_Centrum() const;					// центра фигуры
	const unsigned int Get_ID() const;					// ID фигуры

	// Виртуальные функции:
	virtual void Scale(double scale)       =0;			// масштабирования (относительно центра)
	virtual void Move( double x, double y) =0;			// смемещения центра в (x;y)

	virtual void Rotate( double angle)     =0;			// вращения        (угол в рад., против час. стрелки отн. центра)
};

// //Вывод в поток информации об "фигуре"
std::ostream &operator <<(std::ostream &out, const Shape &shape);