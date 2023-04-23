#include "Circum.h"

// Конструктор
Circum::Circum(double radius, Point &centrum, Color &color) : radius(radius), Shape(color, centrum)
{}

// Узнать радиус окружности
double Circum::Get_Rad() const
{
	return radius;
}

// Смесить окружность в (x;y)
void Circum::Move( double x, double y) 
{
	centrum.x = x;
	centrum.y = y;
}

// Увеличить радиус окружности в scale раз
void Circum::Scale(double scale)     
{
	radius *= scale;
}

// Вывести в поток информации об окружности 
std::ostream &operator <<(std::ostream &out, const Circum &circum)
{
	out << "Radius: "<< circum.Get_Rad() << std::endl;
	out << (const Shape &)circum;

	return out;
}
