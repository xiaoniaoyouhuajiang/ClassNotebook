#include "stdafx.h"
#include "Segment.h"

Segment::Segment(int x, int y, int length, double scale, int angle, string color) {//, string color
	this->X = x;
	this->Y = y;
	this->Length = length;
	this->Color = color;
	this->Angle = angle;
	this->Scale = scale;
	this->Id = ID;
	ID++;
};

Segment::Segment(int length) {
	this->Length = length;
	this->Id = ID;
	ID++;
};

double const Segment::FindProjection() const {//counting by th of sinus
	double pr;
	pr = this->Length *sin(90 - this->Angle);
	return pr;
}

int Segment::GetLength() {

	return this->Length;
}

void Segment::SetLength(int length) {

	this->Length = length;
}

Segment::~Segment() {

};