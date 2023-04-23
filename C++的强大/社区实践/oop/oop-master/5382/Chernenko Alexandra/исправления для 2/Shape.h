#pragma once
#include "stdafx.h"
#include "string"
#define _USE_MATH_DEFINES
#include "math.h"
#include "Point.h"
#include <iostream>
#include <vector>
using namespace std;
class Shape{
private:
	double koeff = M_PI/180;
	double X = 0;
	double Y = 0;//центр фигуры
	int Angle = 0; //угол поворота
	double Scale = 1; // изначальный масштаб
	string Color = "Белый";//цвет фигуры
	int Id; //идентификатор объекта
	vector<Point> Tops;
public:
	static  int ID;
	Shape();
	virtual ~Shape();
	void setAngle(int);
	int getAngle()const;
	void setScale(double);
	double getScale()const;
	void setId(int);
	int getId()const;
	double getX()const;
	double getY()const;
	double getKoeff()const;
	void setPoints(vector<Point>);
	vector<Point> getPoints()const;
	void MoveFigure(double, double); //пермещение
	void TurnFigure(int); //поворот
	void ScaleFigure(double); //масштаб
	string getColorFigure()const;  //получить цвет
	void setColorFigure(string); //задать цвет
	bool hasCommonSide(const Shape&);
	friend ostream&operator<<(ostream&, const Shape&); //поток вывода
	friend ostream&operator<<(ostream&, const Shape*); //поток вывода
	void outPoint(ostream&,int)const;
	virtual void init()=0;
	
};
