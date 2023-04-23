#include "Shape.h"

using namespace custom;

Ellipse::Ellipse(int y, int x, int  smallAxle, int bigAxle, double scale, int angle, string color) {

	X = x;
	Y = y;
	SmallAxle = smallAxle;
	BigAxle = bigAxle;
	Color = color;
	Angle = angle;
	Scale = scale;
	Id = ID;
	ID++;
}

Ellipse::Ellipse(int smallAxle, int bigAxle) {

	SmallAxle = smallAxle;
	BigAxle = bigAxle;
	Id = ID;
	ID++;
}

void Ellipse::MoveFigure(int dx, int dy) {

	X = X + dx;
	Y = Y + dy;
}

void Ellipse::TurnFigure(int angle) {

	Angle = angle;
}

void Ellipse::ScaleFigure(double scale) {

	Scale = scale;
}

string Ellipse::GetColorFigure() {

	return Color;
}

void Ellipse::SetColorFigure(string color) {

	Color = color;
}

int Ellipse::GetSAxle() {

	return SmallAxle;
}

int Ellipse::GetBAxle() {

	return BigAxle;
}

void Ellipse::SetAxles(int  smallAxle, int bigAxle) {

	SmallAxle = smallAxle;
	BigAxle = bigAxle;
}

Ellipse::~Ellipse() {

}
