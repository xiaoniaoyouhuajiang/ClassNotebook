#pragma once
#include "Shape.h"

class Line :
	public Shape
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Line& line);
	void MoveTo(float x, float y) override;
	Line(Point p1, Point p2);
	void Scale(float value) override;
	float Perimeter() override;
	~Line();
};

