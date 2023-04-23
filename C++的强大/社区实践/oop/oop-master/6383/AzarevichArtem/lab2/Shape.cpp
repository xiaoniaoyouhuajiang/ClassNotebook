#include "Shape.h"

//Конструктор
Shape::Shape( Color &color, Point &centrum) : color(color), centrum(centrum) 
{
	static unsigned int count = 0;

	ID = ++count;
}

// Установить(сменить цвет фигуры)
void Shape::Set_Color(char R, char G, char B)
{
	color.RED = R;
	color.GREEN = G;
	color.BLUE = B;
}

//Узнать цвет фигуры
const Color & Shape::Get_Color() const
{
	return color;
}

//Узнать центр фигуры
const Point & Shape::Get_Centrum() const
{
	return centrum;
}	

// Узнать ID фигуры
const unsigned int Shape::Get_ID() const
{
	return ID;
}

//Вывод в поток информации об "фигуре"
std::ostream &operator <<(std::ostream &out, const Shape &shape)
{
	const Color &color = shape.Get_Color();
	const Point &centrum = shape.Get_Centrum();
	out  <<"Centrum: ("<<centrum.x<<" ; "<<centrum.y<<")\nColor: " <<(int)color.RED<<"."<< (int)color.GREEN<<"."<< (int)color.BLUE 
		<<"\nID: " << shape.Get_ID() <<std::endl;
	return out;
}