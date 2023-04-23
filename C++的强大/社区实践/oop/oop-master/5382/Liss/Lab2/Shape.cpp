#include "stdafx.h"
#include "Shape.h"
int Shape::ID = 0;
Shape::~Shape() {

}
void Shape::MoveFigure(int dx, int dy) {

	this->X = this->X + dx;
	this->Y = this->Y + dy;
};
void Shape::TurnFigure(int angle) {

	this->Angle = angle;
}
void Shape::ScaleFigure(double scale) {

	this->Scale = scale;
}

string Shape::GetColorFigure() {

	return this->Color;
}
void Shape::SetColorFigure(string color) {

	this->Color = color;
}
