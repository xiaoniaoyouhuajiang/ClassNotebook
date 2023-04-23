#pragma once

class point
{

private:

	double x, y;

public:

	point();
	point(double InitX, double InitY);

	point(const point& other);
	point& operator=(const point& other);

    point& operator+=(const point &b);
    point& operator-=(const point &b);
    point& operator*=(double val);
    point& operator/=(double val);

    double len() const;

	double getX() const;
	double getY() const;

	void setX(double x);
	void setY(double y);

};

point operator+(point a, const point& b);
point operator-(point a, const point& b);
point operator*(point a, double val);
point operator/(point a, double val);
