#include "Shape.h"

using namespace custom;

Pentagon::Pentagon(int y, int x, int side, double scale, int angle, string color){

	X = x;
	Y = y;
	Side = side;
	Color = color;
	Angle = angle;
	Scale = scale;
	Id = ID;
	ID++;
}

Pentagon::Pentagon(int side) {

	Side = side;
	Id = ID;
	ID++;
}

void Pentagon::MoveFigure(int dx, int dy) {

	X = X + dx;
	Y = Y + dy;
}

void Pentagon::TurnFigure(int angle) {

	Angle = angle;
}

void Pentagon::ScaleFigure(double scale) {

	Scale = scale;
}

string Pentagon::GetColorFigure() {

	return Color;
}

void Pentagon::SetColorFigure(string color) {

	Color = color;
}

int Pentagon::GetSide() {

	return Side;
}

void Pentagon::SetSide(int side) {

	Side = side;
}

Pentagon::~Pentagon()
{

}
