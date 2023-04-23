#include "stdafx.h"
#include "Pentagon.h"
Pentagon::Pentagon(int y, int x, int side, double scale, int angle, string color)// : Pentagon(side)//, string color
{

	this->X = x;
	this->Y = y;
	this->Side = side;
	this->Color = color;
	this->Angle = angle;
	this->Scale = scale;
	this->Id = ID;
	ID++;
	
};
Pentagon::Pentagon(int side) {

	this->Side = side;
	this->Id = ID;
	ID++;
};

double const Pentagon::FindProjection() const{
	double pr;
	pr = this->Side *(sin(108) / sin(36));
	return pr;
}

int Pentagon::GetSide() {

	return this->Side;
}

void Pentagon::SetSide(int side) {

	this->Side = side;
}

Pentagon::~Pentagon() {

};