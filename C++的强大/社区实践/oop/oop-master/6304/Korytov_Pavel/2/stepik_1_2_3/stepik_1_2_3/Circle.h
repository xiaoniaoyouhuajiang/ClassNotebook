#pragma once
#include "Shape.h"
class Circle :
	public Shape
{
public:
	Circle();
	~Circle() = default;
	Circle(Point x, int r, Color clr = Black);
	Circle(int x, int y, int r, Color clr = Black);
	void Enter();
	void Out();
	friend ostream& operator<<(ostream& os, Circle& s);
	void Rand(int min, int max);
	void Scale(int c);
	void Scale(int c, Point cnt);
private:
	int rad;
};

