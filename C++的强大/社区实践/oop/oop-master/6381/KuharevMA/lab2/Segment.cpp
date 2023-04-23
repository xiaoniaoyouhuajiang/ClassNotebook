#include "stdafx.h"

#include "Segment.h"

Segment::Segment(int x, int y, int length, double scale, int angle, string color) {

	X = x;
	Y = y;
	Length = length;
	Color = color;
	Angle = angle;
	Scale = scale;
	Id = ID;
	ID++;
};
Segment::Segment(int length) {

	Length = length;
	Id = ID;
	ID++;
};
int Segment::GetLength() {

	return Length;
}
void Segment::SetLength(int length) {

	Length = length;
}

Segment::~Segment() {

};