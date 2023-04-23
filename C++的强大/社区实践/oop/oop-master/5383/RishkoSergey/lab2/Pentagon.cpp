#include "stdafx.h"
#include "math.h"
#include <cmath>
#include "Pentagon.h"
#include "Shape.h"

using namespace std;

Pentagon::Pentagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5)
{
	X1 = x1;
	X2 = x2;
	X3 = x3;
	X4 = x4;
	X5 = x5;
	Y1 = y1;
	Y2 = y2;
	Y3 = y3;
	Y4 = y4;
	Y5 = y5;
	Id = ID;
	ID++;
}

void Pentagon::GetCenter()
{
	CenterX = (X1 + X2 + X3 + X4 + X5) / 5;
	CenterY = (Y1 + Y2 + Y3 + Y4 + Y5) / 5;
}

void Pentagon::MoveFigure(double dx, double dy)
{
	GetCenter();
	X1 += dx;
	Y1 += dy;
	X2 += dx;
	Y2 += dy;
	X3 += dx;
	Y3 += dy;
	X4 += dx;
	Y4 += dy;
	X5 += dx;
	Y5 += dy;
	CenterX += dx;
	CenterY += dy;
}

void Pentagon::TurnFigure(double Angle)
{
	GetCenter();
	double radAngle = Angle*3.14159 / 180;
	double TempX = X1, TempY = Y1;
	X1 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y1 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
	TempX = X2; TempY = Y2;
	X2 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y2 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
	TempX = X3; TempY = Y3;
	X3 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y3 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
	TempX = X4; TempY = Y4;
	X4 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y4 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
	TempX = X5; TempY = Y5;
	X5 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y5 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
}

void Pentagon::ScaleFigure(double Scale)
{
	GetCenter();
	X1 = CenterX + (X1 - CenterX)*Scale;
	Y1 = CenterY + (Y1 - CenterY)*Scale;
	X2 = CenterX + (X2 - CenterX)*Scale;
	Y2 = CenterY + (Y2 - CenterY)*Scale;
	X3 = CenterX + (X3 - CenterX)*Scale;
	Y3 = CenterY + (Y3 - CenterY)*Scale;
	X4 = CenterX + (X4 - CenterX)*Scale;
	Y4 = CenterY + (Y4 - CenterY)*Scale;
	X5 = CenterX + (X5 - CenterX)*Scale;
	Y5 = CenterY + (Y5 - CenterY)*Scale;
}

double Pentagon::Perimetr()
{
	Length = sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2));
	Per = Length;
	Length = sqrt(pow((X3 - X2), 2) + pow((Y3 - Y2), 2));
	Per += Length;
	Length = sqrt(pow((X4 - X3), 2) + pow((Y4 - Y3), 2));
	Per += Length;
	Length = sqrt(pow((X5 - X4), 2) + pow((Y5 - Y4), 2));
	Per += Length;
	Length = sqrt(pow((X1 - X5), 2) + pow((Y1 - Y5), 2));
	Per += Length;
	Per = round(Per * 100000) / 100000.;
	return Per;
}

Pentagon::~Pentagon()
{

};
