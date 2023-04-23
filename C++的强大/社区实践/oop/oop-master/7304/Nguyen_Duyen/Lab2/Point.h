#pragma once
class Point
{
protected:
	double x, y;
public:
	Point();
	Point(double, double);

	double getX() const;
	double getY() const;
	void setX(double);
	void setY(double);
	~Point();
};

