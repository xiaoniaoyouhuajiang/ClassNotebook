#pragma once
#include <iostream>
#include <vector>
#include <string>
#define PI            3.14159265358979323846

class Point
{
	double x;
	double y;
public:
	Point()
	{
		this->x = 0;
		this->y = 0;
	}
	Point(double x, double y);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
};
class Shape
{
protected:
	Point center;
	int angle;
	std::string color = "black";
	std::vector<Point> points;
public:
	Shape(Point center)
	{
		this->center = center;
		this->angle = 0;
		this->color = "black";
	}
	void move(Point newCenter);
	void turn(int angle);
	void zoom(int k);
	void setColor(std::string color);
	std::string getColor();
	Point getCenter();
	virtual void printOUT(std::ostream& out) = 0;
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}

};