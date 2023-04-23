#pragma once
#include "Shape.h"
class Pentagon :
	public Shape
{
private:
	Point p3;
	Point p4;
	Point p5;
	Point getCenter() override;
public:
	friend std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon);
	Pentagon(Point p1, Point p2, Point p3, Point p4, Point p5);
	void MoveTo(float x, float y) override;
	void Rotate(int angle) override;
	void Scale(float value) override;

	~Pentagon();
};

