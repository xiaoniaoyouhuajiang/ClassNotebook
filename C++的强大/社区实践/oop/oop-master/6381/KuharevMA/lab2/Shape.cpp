#include "stdafx.h"
#include "Shape.h"
int Shape::ID = 0;
Shape::~Shape() {

}

void Shape::MoveFigure(int dx, int dy) {

	X = X + dx;
	Y = Y + dy;
};

void Shape::TurnFigure(int angle) {

	Angle = angle;
}


void Shape::ScaleFigure(double scale) {

	Scale = scale;
}
string Shape::GetColorFigure() {

	return Color;
}
void Shape::SetColorFigure(string color) {

	Color = color;
}