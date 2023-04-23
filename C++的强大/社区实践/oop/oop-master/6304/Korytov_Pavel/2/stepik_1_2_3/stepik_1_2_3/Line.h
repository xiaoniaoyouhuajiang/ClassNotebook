#pragma once
#include <cmath>
#include "Shape.h"

class Line :
	public Shape
{
public:
	Line();
	~Line() = default;
	Line(Point a, Point b, Color clr = Black);
	Line(int x1, int y1, int x2, int y2, Color clr = Black);
	//Int-out
	void Enter();
	//Different points
	Point Start();
	Point End();
	Point Delta();
	//Geometry
	void RotateAroundStart(int deg);
	void RotateAroundEnd(int deg);
	void MoveAtCoords(Point newp);
	double Length();
	int ScalarMult(Line& l2);
};

