#pragma once
#include <cmath>
#include <iostream>

class Point	// класс вершина						
{
public:
	double x;
	double y;	// координаты вершины
	Point();
	~Point();
	explicit Point(double x = 0, double y = 0);
	Point(const Point & p);
	Point(Point && p);
	Point & operator = (const Point & p);
	Point & operator = (Point && p);
	Point operator += (const Point & p);
	Point operator -= (const Point & p);
	Point operator *= (const Point & p);
	Point operator *= (const double value);
	Point operator /= (const Point & p);
	Point operator /= (const double value);
	Point operator + (const Point & p) const;
	Point operator - (const Point & p) const;
	Point operator * (const double value) const;
	Point operator / (const double value) const;
	Point operator + ();
	Point operator - ();
	const bool operator == (const Point & p);
	double get_x() const;
	double get_y() const;
	double & get_x();
	double & get_y();
	void set_x(const double & x);
	void set_y(const double & y);
	double abs() const;
	void rotate(double angle);						// поворот на определенны угол за счет сещения координат
	double length(const Point & p)	const;			// длина стороны, расстояние между точками
	void scale(const double coef);					// масштабирование
	void move(const Point & p);						// сдвиг
	bool equationOfTheLine(const Point & p1, const Point & p2) const;
	friend std::ostream & operator << (std::ostream & out_, const Point & p);
	void swap(Point & p);
private:
	void out(std::ostream & out_) const;
};