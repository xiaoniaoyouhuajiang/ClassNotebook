#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "math.h"
#include <string>
#include <iostream>

using namespace std;
struct CS
{
	double x;
	double y;
};

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Color(char _r, char _g, char _b) {
		r = _r;
		g = _g;
		b = _b;
	}
	Color();
};

class Shape
{
protected:
	static int counter;
	int id;
	CS center;
	Color currentColor;
	double AB;
	double BC;
	double AC;
private:

public:
	Shape(Color _color);
	virtual ostream &put(ostream& out) const = 0;
	virtual void Move(double _x, double _y) = 0;
	virtual void Rotate(double _angle) = 0;
	virtual void Scale(double _scale) = 0;
	//virtual void SetColor(string _color);
	//virtual Color GetColor();
	virtual bool IsInsideOfAnother(const Shape& other);
};
#endif