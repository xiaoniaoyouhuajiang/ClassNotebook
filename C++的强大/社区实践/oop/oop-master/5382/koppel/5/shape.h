#pragma once
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <map>
#include <ctime>
#include <algorithm>
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

template <typename T>
bool float_comparison(T f1, T f2)
{
	return (fabs(f1 - f2) <= std::numeric_limits<T>::epsilon());
}

class Point {
public:

	double x;
	double y;
	Point::Point() : x(0), y(0) {}
	Point::Point(double x, double y) : x(x), y(y) {}

	bool Point::distance(const Point &smth) const
	{
		double dx = smth.x - x;
		double dy = smth.y - y;
		return sqrt(dx*dx + dy*dy);
	}

	friend bool operator == (const Point& first, const Point& second) {
		return ((float_comparison(first.x, second.x)) && (float_comparison(first.y, second.y)));
	}

	friend bool operator < (const Point& first, const Point& second) {
		if (float_comparison(first.x, second.x))
			return (first.y < second.y);
		else
			return (first.x < second.x);
	}

	friend bool operator <= (const Point& first, const Point& second) {
		return ((first < second) || (first == second));
	}

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
	virtual void print(ostream &ost) = 0;
	virtual void rotate(int new_angle) = 0;
	virtual ~Shape() {}


	friend ostream &operator << (ostream &ost, Shape& Object)
	{
		Object.print(ost);
		return ost;
	}

	bool common_vertex(const Shape& other) const
	{
		return std::find_first_of(vertex.begin(), vertex.end(), other.get_vector().begin(), other.get_vector().end()) != vertex.end();

	}
};


class Rectangle : public Shape {
private:
	double width;
	double height;

public:
	Rectangle(Point current_center, int angle, double scale, double width, double height) :
		Shape(current_center, angle, scale),
		width(width),
		height(height)
	{
		vertex.resize(4);

		vertex[0].x = vertex[1].x = current_center.x - width / 2;
		vertex[2].x = vertex[3].x = current_center.x + width / 2;
		vertex[0].y = vertex[2].y = current_center.y + height / 2;
		vertex[3].y = vertex[1].y = current_center.y - height / 2;

		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("Negative width or/and height!?!");
		}
	}


	void print(ostream &ost)
	{
		setlocale(LC_ALL, "Rus");
		ost << endl << "Rectangle" << endl;
		ost << endl << "Coordinates: " <<
			"(" << vertex[1].x << ";" << vertex[1].y << ")" <<
			"(" << vertex[0].x << ";" << vertex[0].y << ")" <<
			"(" << vertex[2].x << ";" << vertex[2].y << ")" <<
			"(" << vertex[3].x << ";" << vertex[3].y << ")" << endl;
		ost << endl << "Angle: " << angle << endl;
		color_type temp = get_color();
		ost << endl << "Color: " << temp << endl << endl;
	}

	void move(Point new_center)
	{
		current_center.x = new_center.x;
		current_center.y = new_center.y;
		vertex[0].x = vertex[1].x = new_center.x - width / 2;
		vertex[2].x = vertex[3].x = new_center.x + width / 2;
		vertex[0].y = vertex[2].y = new_center.y + height / 2;
		vertex[3].y = vertex[1].y = new_center.y - height / 2;
	}

	void Scale(double scale)
	{
		width *= scale;
		height *= scale;
		vertex[0].x = vertex[1].x = current_center.x - width / 2;
		vertex[2].x = vertex[3].x = current_center.x + width / 2;
		vertex[0].y = vertex[2].y = current_center.y + height / 2;
		vertex[3].y = vertex[1].y = current_center.y - height / 2;
	}

	void rotate(int new_angle)
	{
		double angle = new_angle * 3.14 / 180;
		Point temp_left_top;
		Point temp_left_bottom;
		Point temp_right_top;
		Point temp_right_bottom;
		temp_left_top.x = vertex[1].x;
		temp_left_bottom.x = vertex[0].x;
		temp_right_top.x = vertex[3].x;
		temp_right_bottom.x = vertex[2].x;
		temp_left_top.y = vertex[1].y;
		temp_left_bottom.y = vertex[0].y;
		temp_right_top.y = vertex[3].y;
		temp_right_bottom.y = vertex[2].y;

		vertex[1].x = current_center.x + (temp_left_top.x - current_center.x) * cos(angle) - (temp_left_top.y - current_center.y) * sin(angle);
		vertex[1].y = current_center.y + (temp_left_top.x - current_center.x) * sin(angle) + (temp_left_top.y - current_center.y) * cos(angle);
		vertex[3].x = current_center.x + (temp_right_top.x - current_center.x) * cos(angle) - (temp_right_top.y - current_center.y) * sin(angle);
		vertex[3].y = current_center.y + (temp_right_top.x - current_center.x) * sin(angle) + (temp_right_top.y - current_center.y) * cos(angle);
		vertex[0].x = current_center.x + (temp_left_bottom.x - current_center.x) * cos(angle) - (temp_left_bottom.y - current_center.y) * sin(angle);
		vertex[0].y = current_center.y + (temp_left_bottom.x - current_center.x) * sin(angle) + (temp_left_bottom.y - current_center.y) * cos(angle);
		vertex[2].x = current_center.x + (temp_right_bottom.x - current_center.x) * cos(angle) - (temp_right_bottom.y - current_center.y) * sin(angle);
		vertex[2].y = current_center.y + (temp_right_bottom.x - current_center.x) * sin(angle) + (temp_right_bottom.y - current_center.y) * cos(angle);
		angle += new_angle;

	}

};


class Pentagon : public Shape {

public:

	Pentagon(Point current_center, int angle, double scale, vector <Point> vertex)//Pentagon
		:Shape(current_center, angle, scale)
	{//TCentr = vertex[4]
		sort(vertex.begin(), vertex.end());
		if (adjacent_find(vertex.begin(), vertex.end()) != vertex.end()) throw std::invalid_argument("It's not a Pentagon!");
		this->vertex = vertex;
	}


	void move(Point new_center)
	{
		double X = new_center.x - current_center.x;
		double Y = new_center.y - current_center.y;
		for (int i = 0; i < 5; i++)
		{
			vertex[i].x += X;
			vertex[i].y += Y;
		}
	}

	void Scale(double scale)
	{
		for (int i = 0; i < 5; i++)
		{
			vertex[i].x *= scale;
			vertex[i].y *= scale;
		}
	}


	void rotate(int new_angle)
	{
		double angle = new_angle;
		Point temp_left_top;
		Point temp_left_bottom;
		Point temp_right_top;
		Point temp_right_bottom;
		Point tempTCenter;
		tempTCenter.x = vertex[4].x;
		tempTCenter.y = vertex[4].y;
		temp_left_top.x = vertex[1].x;
		temp_left_bottom.x = vertex[0].x;
		temp_right_top.x = vertex[3].x;
		temp_right_bottom.x = vertex[2].x;
		temp_left_top.y = vertex[1].y;
		temp_left_bottom.y = vertex[0].y;
		temp_right_top.y = vertex[3].y;
		temp_right_bottom.y = vertex[2].y;

		vertex[1].x = current_center.x + (temp_left_top.x - current_center.x) * cos(angle) - (temp_left_top.y - current_center.y) * sin(angle);
		vertex[1].y = current_center.y + (temp_left_top.x - current_center.x) * sin(angle) + (temp_left_top.y - current_center.y) * cos(angle);
		vertex[3].x = current_center.x + (temp_right_top.x - current_center.x) * cos(angle) - (temp_right_top.y - current_center.y) * sin(angle);
		vertex[3].y = current_center.y + (temp_right_top.x - current_center.x) * sin(angle) + (temp_right_top.y - current_center.y) * cos(angle);
		vertex[0].x = current_center.x + (temp_left_bottom.x - current_center.x) * cos(angle) - (temp_left_bottom.y - current_center.y) * sin(angle);
		vertex[0].y = current_center.y + (temp_left_bottom.x - current_center.x) * sin(angle) + (temp_left_bottom.y - current_center.y) * cos(angle);
		vertex[2].x = current_center.x + (temp_right_bottom.x - current_center.x) * cos(angle) - (temp_right_bottom.y - current_center.y) * sin(angle);
		vertex[2].y = current_center.y + (temp_right_bottom.x - current_center.x) * sin(angle) + (temp_right_bottom.y - current_center.y) * cos(angle);
		angle += new_angle;
	}


	void print(ostream &ost)
	{
		setlocale(LC_ALL, "Rus");
		ost << endl << "Pentagon" << endl;
		ost << endl << "Coordinates: " << "(" << vertex[4].x << ";" << vertex[4].y << ")" <<
			"(" << vertex[1].x << ";" << vertex[1].y << ")" <<
			"(" << vertex[0].x << ";" << vertex[0].y << ")" <<
			"(" << vertex[2].x << ";" << vertex[2].y << ")" <<
			"(" << vertex[3].x << ";" << vertex[3].y << ")" << endl;
		ost << endl << "Angle: " << angle << endl;
		color_type temp = get_color();
		ost << endl << "Color: " << temp << endl << endl;

	}
};


class Star :public Shape {
private:
	int starAngle = 0;
	double radius;

public:
	Star(Point current_center, int angle, double scale, int radius)
		:Shape(current_center, angle, scale), radius(radius) {
		vertex[4].x = current_center.x + radius*cos(starAngle * 3.14 / 180);
		vertex[4].y = current_center.y - radius*sin(starAngle * 3.14 / 180);
		starAngle += 72;
		vertex[2].x = current_center.x + radius*cos(starAngle * 3.14 / 180);
		vertex[2].y = current_center.y - radius*sin(starAngle * 3.14 / 180);
		starAngle += 72;
		vertex[3].x = current_center.x + radius*cos(starAngle * 3.14 / 180);
		vertex[3].y = current_center.y + radius*cos(starAngle * 3.14 / 180);
		starAngle += 72;
		vertex[0].x = current_center.x + radius*cos(starAngle * 3.14 / 180);
		vertex[0].y = current_center.y + radius*cos(starAngle * 3.14 / 180);
		starAngle += 72;
		vertex[1].x = current_center.x + radius*cos(starAngle * 3.14 / 180);
		vertex[1].y = current_center.y + radius*cos(starAngle * 3.14 / 180);

	}

	void move(Point new_center)
	{
		double X = new_center.x - current_center.x;
		double Y = new_center.y - current_center.y;
		for (int i = 0; i < 5; i++)
		{
			vertex[i].x += X;
			vertex[i].y += Y;
		}
	}

	void Scale(double scale)
	{
		for (int i = 0; i < 5; i++)
		{
			vertex[i].x *= scale;
			vertex[i].y *= scale;
		}
	}


	void rotate(int new_angle)
	{
		double angle = new_angle;
		Point temp_left_top;
		Point temp_left_bottom;
		Point temp_right_top;
		Point temp_right_bottom;
		Point tempTCenter;
		tempTCenter.x = vertex[4].x;
		tempTCenter.y = vertex[4].y;
		temp_left_top.x = vertex[1].x;
		temp_left_bottom.x = vertex[0].x;
		temp_right_top.x = vertex[3].x;
		temp_right_bottom.x = vertex[2].x;
		temp_left_top.y = vertex[1].y;
		temp_left_bottom.y = vertex[0].y;
		temp_right_top.y = vertex[3].y;
		temp_right_bottom.y = vertex[2].y;

		vertex[1].x = current_center.x + (temp_left_top.x - current_center.x) * cos(angle) - (temp_left_top.y - current_center.y) * sin(angle);
		vertex[1].y = current_center.y + (temp_left_top.x - current_center.x) * sin(angle) + (temp_left_top.y - current_center.y) * cos(angle);
		vertex[3].x = current_center.x + (temp_right_top.x - current_center.x) * cos(angle) - (temp_right_top.y - current_center.y) * sin(angle);
		vertex[3].y = current_center.y + (temp_right_top.x - current_center.x) * sin(angle) + (temp_right_top.y - current_center.y) * cos(angle);
		vertex[0].x = current_center.x + (temp_left_bottom.x - current_center.x) * cos(angle) - (temp_left_bottom.y - current_center.y) * sin(angle);
		vertex[0].y = current_center.y + (temp_left_bottom.x - current_center.x) * sin(angle) + (temp_left_bottom.y - current_center.y) * cos(angle);
		vertex[2].x = current_center.x + (temp_right_bottom.x - current_center.x) * cos(angle) - (temp_right_bottom.y - current_center.y) * sin(angle);
		vertex[2].y = current_center.y + (temp_right_bottom.x - current_center.x) * sin(angle) + (temp_right_bottom.y - current_center.y) * cos(angle);
		angle += new_angle;
	}

	void print(ostream &ost)
	{
		setlocale(LC_ALL, "Rus");
		ost << endl << "Pentagram" << endl;
		ost << endl << "Coordinates: " << "(" << vertex[4].x << ";" << vertex[4].y << ")" <<
			"(" << vertex[1].x << ";" << vertex[1].y << ")" <<
			"(" << vertex[0].x << ";" << vertex[0].y << ")" <<
			"(" << vertex[2].x << ";" << vertex[2].y << ")" <<
			"(" << vertex[3].x << ";" << vertex[3].y << ")" << endl;
		ost << endl << "Angle: " << angle << endl;
		color_type temp = get_color();
		ost << endl << "Color: " << temp << endl << endl;

	}

};


