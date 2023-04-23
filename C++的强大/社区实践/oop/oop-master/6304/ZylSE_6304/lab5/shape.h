#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <locale.h>

using namespace std;

#define PI            3.14159265358979323846

class Point {
public:
	double x;
	double y;
	Point(double x, double y) : x(x), y(y) {}
};

class Shape {
public:
	Shape(double x, double y) :color("white"), center(x, y), angle(0) {}

	void setColor(string color);

	void reLocate(double x, double y);
	virtual void zoom(double n) = 0;
	void prepare_for_zoom(double& n);

	void turn(int angl);

	virtual void printOUT(ostream& out) = 0; // печать информации о фигуре
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}

public:
	string color;
	Point center;
	int angle;
	vector<Point> points;
};

class Square : public Shape {
public:
	Square(Point center, double side) : Shape(center.x, center.y), side(side) {
		points.push_back({ center.x - side / 2, center.y + side / 2 });
		points.push_back({ center.x + side / 2, center.y + side / 2 });
		points.push_back({ center.x + side / 2, center.y - side / 2 });
		points.push_back({ center.x - side / 2, center.y - side / 2 });
	}

	void zoom(double n);

	void printOUT(ostream& out);

private:
	double side;
};


class Rhomb : public Shape {
public:
	Rhomb(Point center, double diagonal_half_1, double diagonal_half_2) : Shape(center.x, center.y), side(sqrt(pow(diagonal_half_1, 2) + pow(diagonal_half_2, 2))) {
		points.push_back({ center.x - diagonal_half_1, center.y });
		points.push_back({ center.x, center.y + diagonal_half_2 });
		points.push_back({ center.x + diagonal_half_1, center.y });
		points.push_back({ center.x , center.y - diagonal_half_2 });
	}

	void zoom(double n);

	void printOUT(ostream& out);

private:
	double side;
};

class Trapezium : public Shape {
public:
	Trapezium(Point center, double side_1, double side_2, double h) : Shape(center.x, center.y), side_1(side_1), side_2(side_2), h(h) {
		points.push_back({ center.x - side_1 / 2, center.y + h / 2 });
		points.push_back({ center.x + side_1 / 2, center.y + h / 2 });
		points.push_back({ center.x + side_2 / 2, center.y - h / 2 });
		points.push_back({ center.x - side_2 / 2, center.y - h / 2 });
	}

	void zoom(double n);

	void printOUT(ostream& out);

private:
	double side_1;
	double side_2;
	double h;
};