#pragma once
#include <iostream>
#include <vector>
#include <string>
#define PI            3.14159265358979323846
using namespace std;

class Point {
public:
	double x;
	double y;
	Point(double x, double y) : x(x), y(y) {}
};

class Shape {
protected:
	double angle;
	vector<Point> points;
	string color = "black";
	Point center;
public:
	Shape(double x, double y) : color("black"), center(x, y), angle(0) {}
	void setColor(string color);
	void reLocate(double x, double y);
	virtual void zoom(double n) = 0;
	void prepare_for_zoom(double& n);
	void turn(int angl);
	Point getCenter();
	string getColor();
	virtual void printOUT(ostream& out) = 0; // печать информации о фигуре
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}
};