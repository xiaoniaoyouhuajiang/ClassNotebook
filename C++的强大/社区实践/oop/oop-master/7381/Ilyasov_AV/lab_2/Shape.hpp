#ifndef SHAPE_HPP
#define SHAPE_HPP

#define _USE_MATH_DEFINES

#include <iostream>

size_t ID = 0;

struct Point {
	double x;
	double y;

	Point(const double x = 0, const double y = 0): x(x), y(y) {}

	friend Point operator +=(Point &P1, const Point &P2) {
		return Point(P1.x = P1.x + P2.x, P1.y = P1.y + P2.y);
	}

	friend Point operator *=(Point &P1, const double number) {
		return Point(P1.x = P1.x * number, P1.y = P1.y * number);
	}

	friend std::ostream& operator <<(std::ostream &out, const Point obj) {
		out << "(" << obj.x << ", " << obj.y << ")";
		return out;
	}
};

struct Color {
	char r;
	char g;
	char b;

	Color(const char r, const char g, const char b): r(r), g(g), b(b) {}

	friend std::ostream& operator <<(std::ostream &out, const Color obj) {
		out << "(" << int(obj.r) << ", " << int(obj.g) << ", " << int(obj.b) << ")";
		return out;
	}
};

class Shape {
protected:
	Point centre;
	Point vertex[4];
	Color color;
	size_t id;
public:
	Shape(const Point centre = Point(0, 0), 
		  const Color color = Color(0, 0, 0))
		  : centre(centre), color(color), id(++ID) {};
	~Shape() {};
	
	Color getColor() { return color; }

	void setColor(const char r, const char g, const char b) {
		this->color = Color(r, g, b);
	}

	virtual void rotate(const double angle) = 0;
	virtual void moveTo(const Point point) = 0;
	virtual void scale(const double increase_factor) = 0;
};

#endif