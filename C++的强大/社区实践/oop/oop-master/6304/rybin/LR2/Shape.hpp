#pragma once

#include <string>
#include <vector>
#include <ostream>

struct Point
{
	double m_x;
	double m_y;
};

std::ostream & operator<<(std::ostream & out, const Point& point);
std::ostream & operator<<(std::ostream & out, const std::vector<Point>& points);
bool operator==(const Point& lhs, const Point& rhs);

const std::string default_color = "black";
const Point default_point = { 0.0, 0.0 };
const double default_size = 1.0;

enum what { CIRCLE, SQUARE, TRIANGLE };
enum rot_angle { NIL, RIGHT90, RIGHT180, LEFT90, LEFT180 };

std::ostream & operator<<(std::ostream & out, const what& type);
std::ostream & operator<<(std::ostream & out, const rot_angle& angle);

class Shape
{
public:
	Shape(std::string color = default_color, double size = default_size);
	virtual ~Shape() = default;

	std::string get_color() const;

	void set_color(std::string color);

	virtual what id() const = 0;
	virtual void move(Point to_move) = 0;
	virtual void rotate(rot_angle angle) = 0;
	virtual void zoom(double coef) = 0;
	virtual std::ostream& operator<<(std::ostream& out) const = 0;

protected:
	std::string m_color;
	double m_size;
};

class Circle : public Shape
{
public:
	Circle(std::string color = default_color, double radius = default_size, Point center = default_point);
	what id() const override;
	void move(Point to_move) override;
	void rotate(rot_angle angle) override;
	void zoom(double coef) override;
	std::ostream& operator<<(std::ostream& out) const override;
protected:
	Point m_center;
};

class Square : public Shape
{
public:
	Square(std::string color = default_color, double size = default_size, Point bottom_left = default_point);
	what id() const override;
	void move(Point to_move) override;
	void rotate(rot_angle angle) override;
	void zoom(double coef) override;
	std::ostream& operator<<(std::ostream& out) const override;
protected:
	std::vector<Point> m_points;
};

class Triangle : public Shape
{
public:
	Triangle(std::string color = default_color, double size = default_size, Point bottom_left = default_point);
	what id() const override;
	void move(Point to_move) override;
	void rotate(rot_angle angle) override;
	void zoom(double coef) override;
	std::ostream& operator<<(std::ostream& out) const override;
protected:
	std::vector<Point> m_points;
	rot_angle m_angle;
};