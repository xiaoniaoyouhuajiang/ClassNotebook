#include "stdafx.h"
#include "Ellips.h"
Ellips::Ellips(int y, int x, int  smallAxle, int bigAxle, double scale, int angle, string color) {

	X = x;
	Y = y;
	SmallAxle = smallAxle;
	BigAxle = bigAxle;
	Color = color;
	Angle = angle;
	Scale = scale;
	Id = ID;
	ID++;
};
Ellips::Ellips(int  smallAxle, int bigAxle) {

	SmallAxle = smallAxle;
	BigAxle = bigAxle;
	Id = ID;
	ID++;
};
int Ellips::GetSAxle() {

	return SmallAxle;
}
int Ellips::GetBAxle() {

	return BigAxle;
}
void Ellips::SetAxles(int  smallAxle, int bigAxle) {

	SmallAxle = smallAxle;
	BigAxle = bigAxle;
}
Ellips::~Ellips() {

};