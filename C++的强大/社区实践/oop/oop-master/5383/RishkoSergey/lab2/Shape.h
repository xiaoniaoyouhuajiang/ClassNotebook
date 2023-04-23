#pragma once
#include "stdafx.h"
#include "string"
#include "math.h"
using namespace std;
class Shape{
public:
	static  int ID;
	double CenterX, CenterY;

	virtual void GetCenter() = 0;
	virtual ~Shape();
	virtual void MoveFigure(double, double) = 0; //перемещение
	virtual void TurnFigure(double) = 0; //поворот
	virtual void ScaleFigure(double) = 0; //масштаб
	//virtual void Perimetr() = 0;
	/*virtual string GetColorFigure() = 0; //получить цвет
	virtual void SetColorFigure(string) = 0; //задать цвет*/
	friend ostream&operator<<(ostream&, const Shape&); //поток вывода

};

