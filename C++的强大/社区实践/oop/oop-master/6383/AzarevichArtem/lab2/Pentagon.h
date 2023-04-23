#pragma once
#include "Shape.h"


// Вращение и масштабирование происходит относительно центра тяжести
// фигуры, при условии, что масса находится только в вершинах,
// причём каждая вершина весит одинаково

class Pentagon : public Shape
{
private:
	// Множество точек пятиугольника
	Point points[5];					

public:
	//Конструктор
	Pentagon(Point &a0, Point &a1, Point &a2, Point &a3, Point &a4, Color &color);

	//Узнать точки пятиугольника
	const Point *Get_Points() const;

	//Переопределение виртуальных функций
	virtual void Scale(double scale)       override;		//Масштабирование
	virtual void Move( double x, double y) override;		//Перемещение
	virtual void Rotate( double angle)     override;		//Поворот
};

//Вывод в поток информации о пятиугольнике
std::ostream &operator <<(std::ostream &out, const Pentagon &pentagon);