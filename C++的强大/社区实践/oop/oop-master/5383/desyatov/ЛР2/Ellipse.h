#pragma once
#include "Shape.h"
#include "Point.h"

class Ellipse : public Shape
{
protected:
	Point center;
	Point rightEdge;
	Point topEdge;
	string color;
	string type;
	double scale;
	double lenght; //Длина
	double hight; //Высота

public:
	void ShowFigure();
	Ellipse(); //Стандартный конструктор
	Ellipse(double l, double h);

	void Move(double x, double y);
	void ChangeScale(int n);
	void ChangeColor(string c);
	void ChangeAngle(double angle);
	void SetPoints(double a, double b);
	void print(ostream& output);
	double getArea();
	//void Area();
	~Ellipse();
	double static compareAreas(Ellipse ell1, Ellipse ell2);
};