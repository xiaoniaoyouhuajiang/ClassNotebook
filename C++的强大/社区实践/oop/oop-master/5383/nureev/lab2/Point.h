#pragma once

class Point

{

private:

	double X, Y;

public:

	Point();

	Point(double InitX, double InitY);

	double getX();

	double getY();

	void setX(double x);

	void setY(double y);

};