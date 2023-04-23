#include "stdafx.h"
#include "IsoscelesTriangle.h"
#include "Shape.h"
#include "RightTriangle.h"
#include "Quadrate.h"
#include "Functions.h"

#define PI 3.14159265  

IsoscelesTriangle::IsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, Color _color) : Shape(_color)
{
	this->AB = Length(_ax, _ay, _bx, _by);
	this->BC = Length(_bx, _by, _cx, _cy);
	this->AC = Length(_ax, _ay, _cx, _cy);
	IsItTriangle(_ax, _ay, _bx, _by, _cx, _cy);
}

IsoscelesTriangle::~IsoscelesTriangle()
{
}

void IsoscelesTriangle::IsItIsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy)
{
	try {
		if (!(this->AB == this->BC || this->AB == this->AC || this->BC == this->AC)) {
			throw "It isn't isosceles triangle";
		}
		this->points[0].x = _ax;
		this->points[0].y = _ay;
		this->points[1].x = _bx;
		this->points[1].y = _by;
		this->points[2].x = _cx;
		this->points[2].y = _cy;
		NewTriangleCenter(this->points, this->center);
	}
	catch (char *str)
	{
		cout << "It isn't isosceles triangle" << endl << "enter new coordinates using the spacebar and press Enter" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3" << endl;
		cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy;
		this->AB = Length(_ax, _ay, _bx, _by);
		this->BC = Length(_bx, _by, _cx, _cy);
		this->AC = Length(_ax, _ay, _cx, _cy);
		IsItIsoscelesTriangle(_ax, _ay, _bx, _by, _cx, _cy);
	}
}

void IsoscelesTriangle::IsItTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy)
{
	try {
		if (!(this->AB + this->BC > this->AC || this->AC + this->BC > this->AB || this->AB + this->AC > this->BC))
		{
			throw "It isn't triangle";
		}
		IsItIsoscelesTriangle(_ax, _ay, _bx, _by, _cx, _cy);
	}
	catch (char *str) {
		cout << str << endl << "enter new coordinates using the spacebar and press Enter" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3" << endl;
		cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy;
		this->AB = Length(_ax, _ay, _bx, _by);
		this->BC = Length(_bx, _by, _cx, _cy);
		this->AC = Length(_ax, _ay, _cx, _cy);
		IsItTriangle(_ax, _ay, _bx, _by, _cx, _cy);
	}
}


ostream & IsoscelesTriangle::put(ostream & out) const
{
	return out << "This is isosceles triangle" << endl << "Point's coordinates: " << endl << "x1 | " << this->points[0].x << " y1 | " << this->points[0].y << endl << "x2 | " << this->points[1].x << " y2 | " << this->points[1].y << endl << "x3 | " << this->points[2].x << " y3 | " << this->points[2].y << endl << "Center:"<< endl << this->center.x << " " << this->center.y << endl << "Color: " << endl << "Red: " << (int)currentColor.r << " | Green: "<< (int)currentColor.g << " | Blue: "<<(int)currentColor.b << endl << "ID: " << this->id <<  endl << "---------------" << endl;
}

bool IsoscelesTriangle::IsInsideOfAnother(const Shape & other)
{
	int sum = 0;
	for (int i = 0; i < 3; i++) {
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
	if (sum == 3)
		return true;
	else
		return false;
}


void IsoscelesTriangle::Move(double _x, double _y)
{
	MoveShape(this->points, this->center, _x, _y, 3);
	NewTriangleCenter(this->points, this->center);
}


void IsoscelesTriangle::Rotate(double _angle)
{
	RotateShape(this->points, this->center, _angle, 3);
}

void IsoscelesTriangle::Scale(double _scale)
{
	ScaleShape(this->points, this->center, _scale, 3);
}