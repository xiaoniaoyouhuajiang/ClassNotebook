#include "stdafx.h"
#include "Ellips.h"
Ellips::Ellips(int y, int x, int  smallAxle, int bigAxle , double scale, int angle, string color) {//color//, string color

	this->X = x;
	this->Y = y;
	this->SmallAxle = smallAxle;
	this->BigAxle = bigAxle;
    this->Color = color;//color
	this->Angle = angle;
	this->Scale = scale;
	this->Id = ID;
	ID++;
	
};
Ellips::Ellips(int  smallAxle, int bigAxle) {

	this->SmallAxle = smallAxle;
	this->BigAxle = bigAxle;
	this->Id = ID;
	ID++;
};

double const Ellips::FindProjection() const {//x projection
	double pr;
	pr = this->BigAxle *sin(90 - this->Angle);
	return pr;
}

int Ellips::GetSAxle() {

	return this->SmallAxle;
}
int Ellips::GetBAxle() {

	return this->BigAxle;
}
void Ellips::SetAxles(int  smallAxle, int bigAxle) {

	this->SmallAxle = smallAxle;
	this->BigAxle = bigAxle;
}
Ellips::~Ellips() {

};