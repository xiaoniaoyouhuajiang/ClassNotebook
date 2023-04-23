#pragma once
#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include "Shape.h"
class RightTriangle ://прямоугольный
	public Shape
{
	friend ostream &operator<< (ostream &out, Shape &a);
	friend class IsoscelesTriangle;
	friend class Quadrate;
private:
	CS points[3];
	void IsItRightTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
	void IsItTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
public:
	RightTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, Color _color);
	~RightTriangle();
	void Move(double _x, double _y);
	void Rotate(double _angle);
	void Scale(double _scale);
	ostream &put(ostream &out) const;
	bool IsInsideOfAnother(const Shape &other);
};
#endif
