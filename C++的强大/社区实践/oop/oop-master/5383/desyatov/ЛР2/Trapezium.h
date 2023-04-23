#include "Shape.h"
#include "Point.h"
#pragma once

class Trapezium : public Shape
{
protected:
	Point a1;
	Point a2;
	Point a3;
	Point a4;
	Point center;
	double scale;
	string color;
	string type;
	double hight;
	double lenghtBottom;
	double lenghtTop;
	double lenght;

public:
	Trapezium();
	Trapezium(double lenghtTop, double h, double lenghtBottom);
	void ChangeColor(string c); //Поменять цвет

	double static compareAreas(Trapezium trap1, Trapezium trap2);

	void SetPoint(double x, double y, int num);

	void check();

	void getArea();

	void ShowPoints();

	void Move(double x, double y);

	void ChangeScale(int n);

	void ShowFigure();

	void ChangeAngle(double a);

	void print(ostream& output);
	~Trapezium();
};