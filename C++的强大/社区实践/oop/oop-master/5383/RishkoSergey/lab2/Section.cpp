#include "stdafx.h"
#include "math.h"
#include <cmath>
#include "Section.h"
#include "Shape.h"


using namespace std;

Section::Section(double x1, double y1, double x2, double y2)
{
	X1 = x1;
	X2 = x2;
	Y1 = y1;
	Y2 = y2;
	Id = ID;
	ID++;
}

void Section::GetCenter()
{
	CenterX = (X1 + X2) / 2;
	CenterY = (Y1 + Y2) / 2;
}

void Section::MoveFigure(double dx, double dy)
{
	GetCenter();
	X1+= dx;
	Y1+= dy;
	X2+= dx;
	Y2+= dy;
	CenterX += dx;
	CenterY += dy;
}

void Section::TurnFigure(double Angle)
{
	GetCenter();
	double radAngle = Angle*3.14159 / 180;
	double TempX = X1, TempY = Y1;
	X1 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y1= CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
	TempX = X2; TempY = Y2;
	X2 = CenterX + (TempX - CenterX) * cos(radAngle) - (TempY - CenterY) * sin(radAngle);
	Y2 = CenterY + (TempX - CenterX) * sin(radAngle) + (TempY - CenterY) * cos(radAngle);
}

void Section::ScaleFigure(double Scale)
{
	GetCenter();
	X1 = CenterX + (X1 - CenterX)*Scale;
	Y1 = CenterY + (Y1 - CenterY)*Scale;
	X2 = CenterX + (X2 - CenterX)*Scale;
	Y2 = CenterY + (Y2 - CenterY)*Scale;
}

double Section::Perimetr()
{
	Per = sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2));
	Per = round(Per * 100000) / 100000.;
	return Per;
}

Section::~Section()
{

};
