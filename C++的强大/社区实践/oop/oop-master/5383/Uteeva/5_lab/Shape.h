#pragma once

#ifndef OOP_FIGURE_H
#define OOP_FIGURE_H

#include <iostream>
#include "string"
#include "math.h"
#include <fstream>
#include <vector>
#include <initializer_list>

struct Point
{
	double x;
	double y;

	Point(double x, double y) : x(x), y(y) {}

	friend std::ostream &operator<<(std::ostream &os, const Point &point) {
		os << "x: " << point.x << " y: " << point.y;
		return os;
	}

	bool operator==(const Point &rhs) const {
		return x == rhs.x &&
			y == rhs.y;
	}

	bool operator!=(const Point &rhs) const {
		return !(rhs == *this);
	}

	bool operator<(const Point &rhs) const {
		if (x < rhs.x)
			return true;
		if (rhs.x < x)
			return false;
		return y < rhs.y;
	}

	bool operator>(const Point &rhs) const {
		return rhs < *this;
	}

	bool operator<=(const Point &rhs) const {
		return !(rhs < *this);
	}

	bool operator>=(const Point &rhs) const {
		return !(*this < rhs);
	}
};

struct Color {
	int r = 0;
	int g = 0;
	int b = 0;

	Color(int r, int g, int b) {
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
			throw std::invalid_argument("Неправильно!\n");
		}
		else {
			this->r = r;
			this->g = g;
			this->b = b;
		}
	}

	friend std::ostream &operator<<(std::ostream &os, const Color &color) {
		os << "r: " << color.r << " g: " << color.g << " b: " << color.b;
		return os;
	}
};

using namespace std;
class Shape {
protected:
	static int ID;
	Point center;
	Color color;
	Shape(const Point &center, const Color &color);
	Shape(const Color &color);
	Shape();
	friend ostream&operator<<(ostream &os, const Shape &f); 

	virtual void Move(double dx, double dy);  //перемещение
	virtual void rotate(double angle) = 0;  //поворот
	virtual void ScaleFigure(double scale) = 0; //масштабирование


public:
	
	Point GetCenter() const;
	Color getColor() const;  //получить цвет
    void SetColor(const Color &color);  //задать цвет
	virtual bool isInsideOfAnother(const Shape &other)  const = 0;
	virtual bool isPointInsideOfFigure(const Point &other) const = 0;
	virtual void print(std::ostream &os) = 0;
	static double Length(const Point &p1, const Point &p2);
	static double triangleS(const Point &p1, const Point &p2, const Point &p3);
	virtual ~Shape();
};
#endif