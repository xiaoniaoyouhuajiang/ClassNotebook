#pragma once
#ifndef QUADRATE_H
#define QUADRATE_H

#include "Shape.h"
#include "RightTriangle.h"
#include "IsoscelesTriangle.h"
class Quadrate :
	public Shape
{
	friend class IsoscelesTriangle;
	friend class RightTriangle;
private:
	CS points[4];
	double sides[4];
	double diagonals[2];
	double angles[4];
	void IsItQuadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy);
	void NewQuadrateCenter();
	void NewSizes();
	double Angle(CS p1, CS p2, CS p3);
public:
	Quadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy, Color _color);
	void Move(double _x, double _y);
	void Rotate(double _angle);
	void Scale(double _scale);
	//void SetColor(string _color);
	//string GetColor();
	ostream &put(ostream &out) const;
	bool IsInsideOfAnother(const Shape &other);
	~Quadrate();
};

#endif
