#include "stdafx.h"
#include "Quadrate.h"
#include "Functions.h"
#include<iostream>
#define PI 3.14159265

Quadrate::Quadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy, Color _color):Shape(_color)
{
	IsItQuadrate(_ax, _ay, _bx, _by, _cx, _cy, _dx, _dy);
}

void Quadrate::IsItQuadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy)
{
	this->points[0].x = _ax;
	this->points[0].y = _ay;
	this->points[1].x = _bx;
	this->points[1].y = _by;
	this->points[2].x = _cx;
	this->points[2].y = _cy;
	this->points[3].x = _dx;
	this->points[3].y = _dy;
	NewSizes();
	try {
		if (!((this->sides[0] == this->sides[1]) && (this->sides[1] == this->sides[2]) && (this->sides[2] == this->sides[3]) && (this->sides[3] == this->sides[0]) && (this->diagonals[0] == this->diagonals[1]) && (this->angles[0] == this->angles[1]) && (this->angles[1] == this->angles[2]) && (this->angles[2] == this->angles[3]) && (this->angles[0] == this->angles[3])))
			throw "It isn't quadrate";
		this->points[0].x = _ax;
		this->points[0].y = _ay;
		this->points[1].x = _bx;
		this->points[1].y = _by;
		this->points[2].x = _cx;
		this->points[2].y = _cy;
		this->points[3].x = _dx;
		this->points[3].y = _dy;
		NewQuadrateCenter();

	}
	catch (char *str) {
		cout << str << endl << "Write a new coordinate" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3 | X4 | Y4" << endl;
		cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy >> _dx >> _dy;
		IsItQuadrate(_ax, _ay, _bx, _by, _cx, _cy, _dx, _dy);
	}
}

void Quadrate::NewQuadrateCenter()
{
	center.x = (points[0].x + points[2].x) / 2;
	center.y = (points[0].y + points[2].y) / 2;
}

void Quadrate::NewSizes()
{
	for (int i = 0; i < 3; i++)
	{
		this->sides[i] = Length(this->points[i].x, this->points[i].y, this->points[i + 1].x, this->points[i + 1].y);
	}
	this->sides[3] = Length(this->points[3].x, this->points[3].y, this->points[0].x, this->points[0].y);
	this->diagonals[0] = Length(this->points[0].x, this->points[0].y, this->points[2].x, this->points[2].y);
	this->diagonals[1] = Length(this->points[1].x, this->points[1].y, this->points[3].x, this->points[3].y);
	this->angles[0] = Angle(this->points[0], this->points[3], this->points[1]);
	this->angles[1] = Angle(this->points[1], this->points[0], this->points[2]);
	this->angles[2] = Angle(this->points[2], this->points[1], this->points[3]);
	this->angles[3] = Angle(this->points[3], this->points[2], this->points[0]);
}

void Quadrate::Move(double _x, double _y)
{
	MoveShape(this->points, this->center, _x, _y, 4);
	NewQuadrateCenter();
	NewSizes();
}

void Quadrate::Rotate(double _angle)
{
	RotateShape(this->points, this->center, _angle, 4);
	NewSizes();
}

void Quadrate::Scale(double _scale)
{
	ScaleShape(this->points, this->center, _scale, 4);
	NewSizes();
}

ostream & Quadrate::put(ostream & out) const
{
	return out << "This is quadrate" << endl << "Point's coordinates: " << endl << "x1 | " << this->points[0].x << " y1 | " << this->points[0].y << endl << "x2 | " << this->points[1].x << " y2 | " << this->points[1].y << endl << "x3 | " << this->points[2].x << " y3 | " << this->points[2].y << endl << "x4 | " << this->points[3].x << " y4 | " << this->points[3].y << endl <<"Center: " << endl << this->center.x <<" " << this->center.y << endl << "Color: " << endl << "Red: " << (int)currentColor.r << " | Green: " << (int)currentColor.g << " | Blue: " << (int)currentColor.b << endl << "ID: " << this->id << endl << "---------------" << endl;
}

bool Quadrate::IsInsideOfAnother(const Shape &other)
{
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		if (const IsoscelesTriangle* xyz = dynamic_cast<const IsoscelesTriangle*>(&other))
		{
			sum += ShapeTest(this->points, xyz->points, 3, i);
		}
		else if (const RightTriangle* xyz = dynamic_cast<const RightTriangle*>(&other))
		{
			sum += ShapeTest(this->points, xyz->points, 3, i);
		}
		else if (const Quadrate* xyz = dynamic_cast<const Quadrate*>(&other)) {
			sum += ShapeTest(this->points, xyz->points, 4, i);
		}
	}
	if (sum == 4)
		return true;
	else
		return false;
}

double Quadrate::Angle(CS p1, CS p2, CS p3)
{ 
	return acos(((p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y)) / (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2))*sqrt(pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2))));
}

Quadrate::~Quadrate()
{
}
