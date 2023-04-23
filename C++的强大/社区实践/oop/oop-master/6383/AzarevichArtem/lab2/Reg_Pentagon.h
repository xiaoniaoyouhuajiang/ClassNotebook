#pragma once
#include "circum.h"

// Класс правильный пятиугольник (наследуется от окружности)
class Reg_Pentagon : public Circum
{
private:
	// Вектор(направление) смещения первой точки прав. пятиугольника
	// относительно его центра
	Point vector;

public:
	// Конструктор
	Reg_Pentagon(Point &point_f, Point &centrum, Color &color);
	
	//Узнать вектор(направление)смещения первой точки прав. пятиугольника
	// относительно его центра 
	const Point &Get_Vector() const;

	//Переопределение вирт. функции вращения
	virtual void Rotate( double angle) override ;
};

// Вывод в поток информации о правильном пятиугольнике
std::ostream &operator <<(std::ostream &out, const Reg_Pentagon &reg_pentagon);