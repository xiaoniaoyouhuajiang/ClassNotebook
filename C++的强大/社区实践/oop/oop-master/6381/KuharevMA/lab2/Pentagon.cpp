#include "stdafx.h"
#include "Pentagon.h"
Pentagon::Pentagon(int y, int x, int side, double scale, int angle, string color) {

	X = x;
	Y = y;
	Side = side;
	Color = color;
	Angle = angle;
	Scale = scale;
	Id = ID;
	ID++;
};
Pentagon::Pentagon(int side) {

	Side = side;
	Id = ID;
	ID++;
};
int Pentagon::GetSide() {

	return Side;
}
void Pentagon::SetSide(int side) {

	Side = side;
}
Pentagon::~Pentagon() {

};