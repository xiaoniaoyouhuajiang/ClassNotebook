#include "stdafx.h"
#include "math.h"
#include <cmath>
#include "Ellipse.h"
#include "Shape.h"

using namespace std;

Ellipse::Ellipse(double x1, double y1, double x2, double y2, double x3, double y3)
{
	X1 = x1;
	X2 = x2;
	X3 = x3;
	Y1 = y1;
	Y2 = y2;
	Y3 = y3;
	Id = ID;
	ID++;
}

void Ellipse::GetCenter()
{
	CenterX = X3;
	CenterY = Y3;
}

void Ellipse::MoveFigure(double dx, double dy)
{
	GetCenter();
	X1 += dx;
	Y1 += dy;
	X2 += dx;
	Y2 += dy;
	CenterX += dx;
	CenterY += dy;
}

void Ellipse::TurnFigure(double Angle)
{
	GetCenter();
	double radAngle = Angle*3.14159 / 180;
	double TempX = X1, TempY = Y1;
	X1 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y1 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
	TempX = X2; TempY = Y2;
	X2 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y2 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
}

void Ellipse::ScaleFigure(double Scale)
{
	GetCenter();
	X1 = CenterX + (X1 - CenterX)*Scale;
	Y1 = CenterY + (Y1 - CenterY)*Scale;
	X2 = CenterX + (X2 - CenterX)*Scale;
	Y2 = CenterY + (Y2 - CenterY)*Scale;
}

double Ellipse::Perimetr()
{
	GetCenter();
	Length = sqrt(pow((CenterX - X1), 2) + pow((CenterY - Y1), 2));
	Per = Length;
	Length = sqrt(pow((CenterX - X2), 2) + pow((CenterY - Y2), 2));
	Per += Length;
	Per *= 3.14159265;
	Per = round(Per * 100000) / 100000.;
	return Per;
}

Ellipse::~Ellipse()
{

};
