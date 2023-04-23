#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <cstdint>

typedef unsigned char UCHAR;
typedef unsigned int  UINT;

struct Color {
	UCHAR r;
	UCHAR g;
	UCHAR b;

	Color(UCHAR _r, UCHAR _g, UCHAR _b)
		: r(_r)
		, g(_g)
		, b(_b) {}

	Color() {}
};

template <typename T>
struct Point {
	T x;
	T y;
	static float scale;

	Point(T _x, T _y)
		: x(_x)
		, y(_y) {}

	Point()
		: x(0.0f)
		, y(0.0f) {}

	Point<T> &operator+(const Point<T> &p) {
		x += p.x;
		y += p.y;

		return *this;
	}

	Point<T> &operator-(const Point<T> &p) {
		x -= p.x;
		y -= p.y;

		return *this;
	}
};

typedef Point<float> Pointf;

float Pointf::scale = 1.0f;

class Shape {
protected:
	Color  color;
	float  angle;
	Pointf position;
	
	static uint32_t number_of_shapes;
	const  uint32_t id;

public:
	Shape(Pointf _position, Color _color) 
		: position(_position)
		, color(_color)
		, angle(0)
		, id(++number_of_shapes) {}

	virtual ~Shape() { --number_of_shapes; }

	virtual void rotate(float _angle) = 0 {
		this->angle = _angle;
	}

	virtual void move(Pointf new_position) {
		this->position = new_position;
	}

	void scale(float _pc)  {
		Pointf::scale *= _pc;
	}

	Color getColor() const {
		return this->color;
	}

	void setColor(Color _color) {
		this->color = _color;
	}
};

uint32_t Shape::number_of_shapes = 0;

#endif