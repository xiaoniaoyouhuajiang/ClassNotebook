#pragma once
#include "Shape.h"
class Ellipse :
	public Shape
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Ellipse& ellipse);
	Ellipse(Point p1, Point p2);
	void MoveTo(float x, float y) override;
	void Scale(float value) override;
	float Perimeter() override;
	~Ellipse();
};