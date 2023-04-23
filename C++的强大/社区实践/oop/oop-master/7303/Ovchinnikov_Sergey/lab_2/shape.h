#pragma once
#include <iostream>

struct Color {
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	Color() :red(0), green(0), blue(0) {}
	Color(unsigned char r, unsigned char g, unsigned char b) :red(r), green(g), blue(b) {}
	Color(const Color &color) : red(color.red), green(color.green), blue(color.blue) {}
	Color& operator =(const Color &color) {
		if (this == &color)
			return *this;

		red = color.red;
		green = color.green;
		blue = color.blue;

		return *this;
	}

	void set(unsigned char r, unsigned char g, unsigned char b) {
		red = r;
		green = g;
		blue = b;
	}
};

struct Point {
	double x;
	double y;

	Point() : x(0), y(0) {}
	Point(double _x, double _y) :x(_x), y(_y) {}
	Point(const Point &point) :x(point.x), y(point.y) {}
	Point& operator =(const Point &point) {
		if (this == &point)
			return *this;

		x = point.x;
		y = point.y;

		return *this;
	}
	Point operator+(const Point& p){
		return Point(this->x+p.x,this->y+p.y);
	}

	void set(double _x, double _y) {
		x = _x;
		y = _y;
	}
};


class Shape {

public:
	virtual void Move(const Point& p) = 0;
	virtual void Turn(double angle) = 0;
	virtual void Scale(double scale) = 0;

	void set_color(const Color &color);
	Color get_color() const;
	void set_pos(const Point &point);
	Point get_pos() const;
	double get_angle() const;
	unsigned long get_ID() const;

	friend std::ostream& operator <<(std::ostream &out, const Shape &shape);
	
	static unsigned long global_ID;
protected:
	Shape(const Point& p, const Color& c,double _angle =0);
	Point pos;
	Color color;
	double angle;
	unsigned long ID;
};

