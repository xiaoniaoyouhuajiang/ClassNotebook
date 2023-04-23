#include "Shape.h"

using namespace custom;

Segment::Segment(int x, int y, int length, double scale, int angle, string color) {

	X = x;
	Y = y;
	Length = length;
	Color = color;
	Angle = angle;
	Scale = scale;
	Id = ID;
	ID++;
}

Segment::Segment(int length)
{
	Length = length;
	Id = ID;
    ++ID;
}

void Segment::MoveFigure(int dx, int dy)
{

	X = X + dx;
	Y = Y + dy;

}

void Segment::TurnFigure(int angle)
{
	Angle = angle;
}

void Segment::ScaleFigure(double scale)
{
	Scale = scale;
}

string Segment::GetColorFigure()
{
	return Color;
}
void Segment::SetColorFigure(string color)
{
	Color = color;
}

int Segment::GetLength()
{
	return Length;
}

void Segment::SetLength(int length)
{
	Length = length;
}

Segment::~Segment() {

};
