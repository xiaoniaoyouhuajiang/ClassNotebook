#pragma once
#include "stdafx.h"
#include <iostream>
#include <iterator>
#include "Point.h"
#include "Color.h"

#define M_PI 3.14159265358979323846
using namespace std;
using namespace stdext;

class Shape {
public:
	Shape(int dots = 0, Color clr = Black) : dts(dots), pts(dots ? new Point[dots] : nullptr), col(clr) {}
	virtual ~Shape();
	Color col;
	Point* it(); //Passes throught every point
	//In-out
	virtual void Enter();
	virtual void Out();
	friend ostream& operator<<(ostream& os, Shape& s);
	virtual void Rand(int min, int max);
	//Geometry
	virtual Point GetCenterPoint();
	virtual void Rotate(int deg);
	virtual void Rotate(int deg, Point cnt);
	virtual void Move(Point delta);
	virtual void MoveAtCoords(Point newp);
	virtual void MoveAtCoords(Point newp, Point cnt);
	virtual void Scale(int c);
	virtual void Scale(double c, Point cnt);
protected:
	int dts;
	Point* pts;
private:
	int pos = 0;
};