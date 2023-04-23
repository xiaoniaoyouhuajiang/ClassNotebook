#include "Reg_Pentagon.h"

// Конструктор
Reg_Pentagon::Reg_Pentagon(Point &point_f, Point &centrum, Color &color) : 
 
	Circum( sqrt(  pow(point_f.x - centrum.x, 2) + pow(point_f.y - centrum.y, 2 ) ), centrum, color),
	vector( (point_f.x-centrum.x)/Get_Rad(), (point_f.y - centrum.y)/Get_Rad() )
{}

//Вращение
void Reg_Pentagon::Rotate(double angle) 
{
	double angle_0 = acos(  vector.x  );

		if ( vector.y < 0 ) angle_0 += 2*( acos((double)-1)-angle_0 ); 

	angle_0 += angle;

	vector.x = cos(angle_0);
	vector.y = sin(angle_0);
}


//Узнать вектор(направление)смещения первой точки прав. пятиугольника
// относительно его центра
const Point &Reg_Pentagon::Get_Vector() const
{
	return vector;
}

// Вывод в поток информации о правильном пятиугольнике
std::ostream &operator <<(std::ostream &out, const Reg_Pentagon &reg_pentagon)
{
	const Point &point = reg_pentagon.Get_Vector();
	out << "Vector: (" << point.x << " ; " << point.y << ") "<<std::endl <<(const Circum &)reg_pentagon;

	return out;
}