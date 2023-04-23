#pragma once
#include "stdafx.h"
#include "string"
#include "math.h"
using namespace std;
class Shape {
public:
    Shape();
	virtual ~Shape();
	friend ostream&operator<<(ostream&, const Shape&); //поток вывода
protected: 
	static  int ID;
	int X = 0, Y = 0;//центр фигуры
	int Angle = 0; //угол поворота
	double Scale = 1; // изначальный масштаб
	string Color = "Белый";//цвет фигуры
	virtual void MoveFigure(int, int) = 0; //пермещение
	virtual void TurnFigure(int) = 0; //поворот
	virtual void ScaleFigure(double) = 0; //масштаб
	virtual string GetColorFigure() = 0; //получить цвет
	virtual void SetColorFigure(string) = 0; //задать цвет
};