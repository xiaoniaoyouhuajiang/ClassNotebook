#pragma once
#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <vector>
#include <map>

const float PI = atan(1) * 4;
using namespace std;

enum Colour { red, green, blue, yellow, white, black };

map <Colour, char*> colours_map = {
	{ red, "Red" },
	{ green, "Green" },
	{ blue, "Blue" },
	{ yellow, "Yellow" },
	{ white, "White" },
	{ black, "Black" }
};

struct Point {

	Point() : x(0), y(0) {};
	Point(float x, float y) : x(x), y(y) {}
	float x;
	float y;
	friend Point operator+ (Point const &left, Point const &right) {
		return Point(left.x + right.x, left.y + right.y);
	}

	friend Point operator- (Point const &left, Point const &right) {
		return Point(left.x - right.x, left.y - right.y);
	}

	friend bool operator== (Point const &left, Point const &right) {
		if ((left.x == right.x) && (left.y == right.y))
			return true;
		else return false;
	}

	friend bool operator< (Point const &left, Point const &right) {
		if (left.x == right.x)
			return (left.y < right.y);
		else
			return (left.x < right.x);
	}
};

class Shape {
protected:
	size_t id;
	Colour colour;
	Point center;

	Shape(Colour colour, Point const center) : colour(colour), center(center) {}
	Shape(Colour colour) : colour(colour) {}

	void set_id() {
		static size_t tmp = 0;
		id = ++tmp;
	}

public:

	Colour get_colour() {
		return colour;
	}

	void set_colour(Colour colour) {
		this->colour = colour;
	}

	// Определяет периметр какой фигуры больше
	// Если периметр у текущего объекта >= возвращаем true, иначе - false
	bool is_perimeter_bigger(Shape const& shape)
	{
		return this->perimeter() >= shape.perimeter();
	}

	bool operator< (const Shape& other) {
		return this->perimeter() < other.perimeter();
	}

	bool operator<= (const Shape& other) {
		return this->perimeter() <= other.perimeter();
	}

	virtual void rotate(float angle) = 0; // поворот фигуры относительно начала координат
	virtual void scale(float k) = 0; // масштабирование
	virtual void move(Point const &new_center) = 0; // перемещение
	virtual void show() const = 0; // вывод на экран всех полей фигуры
	virtual float perimeter() const = 0; // подсчет периметра фигуры
	friend ostream& operator<< (ostream &out, Shape const& obj) {
		obj.show();
		out << "Colour - " << colours_map[obj.colour] << endl;
		return out;
	}
};

class Circle : public Shape {
public:
	Circle(Colour colour, Point center, float radius)
		: Shape(colour, center)
		, radius(radius)
	{
		if (this->radius <= 0)
			throw invalid_argument("Wrong input data in Circle!");
		set_id();
	}

	// поворот фигуры относительно начала координат
	void rotate(float angle) override {
		float help_x = this->center.x;
		this->center.x = this->center.x * cos(angle) - this->center.y * sin(angle);
		this->center.y = help_x * sin(angle) + this->center.y * cos(angle);
	}

	// масштабирование фигуры относительно ее центра
	void scale(float k) override {
		radius *= k;
	}

	// перемещение центра фигуры в заданные координаты
	void move(Point const &new_center) override {
		center = new_center;
	}

	// подсчет периметра круга
	float perimeter() const override {
		return ((this->radius) * 2 * PI);
	}

	// вывод на экран информации о фигуре 
	void show() const override {
		cout << "Circle: \n";
		cout << "Center - (" << center.x << " , " << center.y << ") \n";
		cout << "Radius = " << radius << endl;
		cout << "ID - " << id << " \n";
	}

	float radius;
};

class Pentagon : public Circle {
public:
	Pentagon(Colour colour, Point center, float radius) : Circle(colour, center, radius) {
		if (this->radius <= 0)
			throw invalid_argument("Wrong input data in Pentagone!");
		set_id();
	}

	// подсчет периметра правильного пятиугольника
	float perimeter() const override {
		return (10 * this->radius*sin(PI / 5));
	}

	void show() const override {
		cout << "Pentagon: \n";
		cout << "Center - (" << center.x << " , " << center.y << ") \n";
		cout << "Radius = " << radius << endl;
		cout << "ID - " << id << " \n";
	}
};

class Wrong_Pentagon : public Shape {
protected:
	vector <Point> point_i;
	const int count = 5; // количество углов многоугольника

public:
	Wrong_Pentagon(Colour colour, Point const &point_1,
		Point const &point_2, Point const &point_3,
		Point const &point_4, Point const &point_5)

		: Shape(colour)
	{
		point_i = { point_1, point_2, point_3, point_4, point_5 };
		center = (point_1 + point_2 + point_3 + point_4 + point_5);
		center.x /= count;
		center.y /= count;

		sort(point_i.begin(), point_i.end());
		vector<Point>::iterator help = adjacent_find(point_i.begin(), point_i.end());
		if (help != point_i.end())
			throw invalid_argument("Wrong input data in Wrong_Pentagone!");
		set_id();
	}

	// перемещение фигуры в заданные координаты
	void move(Point const &new_center) override {
		Point help(0, 0);
		help = this->center - new_center;
		for (auto&& i : this->point_i) i = i - help;
		this->center = new_center;
	}

	//поворот точки относительно начала координат
	void rotate_point(float angle, Point point)
	{
		float help_x = this->center.x;
		this->center.x = this->center.x * cos(angle) - this->center.y * sin(angle);
		this->center.y = help_x * sin(angle) + this->center.y * cos(angle);
	}

	// поворот фигуры относительно начала координат
	void rotate(float angle) override {
		for (auto&& i : this->point_i) rotate_point(angle, i);
	}

	// увеличивает/уменьшает расстояние между центром фигуры и точкой в k раз
	void scale_point(float k, Point &point)
	{
		Point help(0, 0);
		help = this->center - point;

		if (point.x >= this->center.x)
			point.x = this->center.x - help.x*k;
		else
			point.x = this->center.x + help.x*k;

		if (point.y >= this->center.y)
			point.y = this->center.y - help.y*k;
		else
			point.y = this->center.y + help.y*k;
	}

	// масштабирует неправильный пятиугольник
	void scale(float k) {
		for (auto&& i : this->point_i) scale_point(k, i);
	}

	float perimeter() const override {
		Point help_point;
		float p = 0; // периметр
		for (int i = 0; i < count - 1; i++)
		{
			help_point = point_i[i] - point_i[i + 1];
			p = p + pow((pow(help_point.x, 2) + pow(help_point.y, 2)), 1 / 2); // p +((x^2 + y^2)^1/2)
		}

		help_point = point_i[4] - point_i[0];
		p = p + pow((pow(help_point.x, 2) + pow(help_point.y, 2)), 1 / 2); // p +((x^2 + y^2)^1/2
		return p;
	}

	// вывод на экран информации о фигуре 
	void show() const override {
		cout << "Wrong_Pentagon: \n";
		int j = 1;
		for (auto&& i : this->point_i)
			cout << "Point_" << j << "- (" << i.x << " , " << i.y << ") \n";
		cout << "Center - (" << center.x << " , " << center.y << ") \n";
		cout << "ID - " << id << " \n";
	}
}; 