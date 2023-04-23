#ifndef SHAPE_H
#define SHAPE_H
#include "point.h"
#include <string.h>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

enum color_type { red, orange, yellow, green, blue, violet, white, black };

static map <color_type, char*> map_of_colour = {
	{ red, "Red" },
	{ orange, "Orange" },
	{ yellow, "Yellow" },
	{ green, "Green" },
	{ blue, "Blue" },
	{ violet, "Violet" },
	{ white, "White" },
	{ black, "Black" }
};

class Shape {

private:
	static size_t counter;

protected:
	color_type color = white;
	unsigned ID;
	Point current_center;
	int angle;
	double scale; 
	vector <Point> vertex;

public:

	Shape(Point current_center, int angle = 0, double scale = 1) :
		current_center(current_center), angle(angle), scale(scale), ID(counter++) {}

	virtual ~Shape() {}
	const vector<Point>& get_vector() const {
		return vertex;
	}

	void set_color(color_type parametr)
	{
		color = parametr;
	}


	color_type get_color() const
	{
		return color;
	}


	void set_ID()
	{
		static size_t counter = 0;
		ID = ++counter;
	}

	unsigned get_ID() const
	{
		return ID;
	}


	virtual void Scale(double scale) = 0;
	virtual void move(Point newCenter) = 0;
	friend ostream &operator << (ostream &ost, Shape &object);
	virtual void print(ostream &ost) = 0;
	virtual void rotate(int new_angle) = 0;

	bool common_vertex(const Shape& other) const;


};

#endif
