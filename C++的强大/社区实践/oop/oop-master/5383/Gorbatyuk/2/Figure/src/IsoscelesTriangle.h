#pragma once
#ifndef ISOSCELESTRIANGLE_H
#define ISOSCELESTRIANGLE_H
#include "Shape.h"
class IsoscelesTriangle ://равнобедренный
	public Shape
{
	friend class RightTriangle;
	friend class Quadrate;
private:
	CS points[3];
	void IsItIsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
	void IsItTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
public:
	IsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, Color _color);
	~IsoscelesTriangle();
	void Move(double _x, double _y);
	void Rotate(double _angle);
	void Scale(double _scale);
	bool IsInsideOfAnother(const Shape &other);
	ostream &put(ostream &out) const;
};
#endif
