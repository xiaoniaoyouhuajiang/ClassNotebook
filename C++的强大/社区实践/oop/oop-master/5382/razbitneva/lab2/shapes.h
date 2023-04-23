#pragma once
#include <iostream>
#include <vector>

class Color {
private:
    unsigned long color;

public:
    Color(unsigned long n = 0)
        : color(n)
    {
    }
    void set(unsigned long newcolor)
    {
        color = newcolor;
    }
    unsigned long get()
    {
        return color;
    }
    friend std::ostream& operator<<(std::ostream& os, const Color& tr)
    {
        os << "#" << std::setw(6) << std::setfill('0') << std::hex << tr.color;
        return os;
    }
};
class Point {
private:
    double X, Y;

public:
	Point(double Xn = 0, double Yn = 0): X(Xn), Y(Yn){}

	Point Point::operator+(Point const& t) const
	{
		Point a(X + t.X, Y + t.Y);
		return a;
	};

	bool Point::operator==(Point const &t) const
	{
		return (abs(X - t.X) < DBL_EPSILON  && abs(Y - t.Y) < DBL_EPSILON);
	};

    double getX()
    {
        return X;
    }
    double getY()
    {
        return Y;
    }
    void setX(double a)
    {
        X = a;
    }
    void setY(double a)
    {
        Y = a;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& tr)
    {
        os << "(" << tr.X << "," << tr.Y << ")";
        return os;
    }
};

class Shape {
public:
	Shape(): color(Color(0)){}

    void move(Point newcord)
    {
        cord = newcord;
    }
    void rotate(double angle);
    void scale(double coef);
    Color getColor()
    {
        return color;
    }
    void setColor(Color newcolour)
    {
        color = newcolour;
    }
	
	static bool hasCommonVertex(const Shape& first, const Shape& second);

protected:
    std::vector<Point> point;
    Point cord;
    Color color;
};
void Shape::scale(double coef)
{
    for (int i = 0; i < point.size(); i++) {
        point[i].setX(point[i].getX() * coef);
        point[i].setY(point[i].getY() * coef);
    }
}
void Shape::rotate(double angle)
{
    for (int i = 0; i < point.size(); i++) {
        point[i].setX(point[i].getX() * cos(angle)
            - point[i].getY() * sin(angle));
        point[i].setY(point[i].getX() * sin(angle)
            + point[i].getY() * cos(angle));
    }
}

bool Shape::hasCommonVertex(const Shape& first, const Shape& second){
	for (int i = 0; i < first.point.size(); i++){
		for (int j = 0; j < second.point.size(); j++){
			if (first.point[i] == second.point[j]) return true;
		}
	}

	return false;
}

//===Треугольник===
class Triangle : public Shape {
private:
	double Leng;
public:
	double get_angle();
    Triangle(double leng, Point topp)
    {
        cord = Point(0, 0);
        point.push_back(Point(leng, 0));
        point.push_back(topp);
		this->Leng = leng;
    }
    friend std::ostream& operator<<(std::ostream& os, const Triangle& tr)
    {
        os << "Triangle(" << tr.cord << ";"
           << tr.cord + tr.point[0] << ";" << tr.cord + tr.point[1]
           << "):" << tr.color;
        return os;
    }
};
double Triangle::get_angle(){
	return this->Leng;
}

//===Ромб===
class Rhombus : public Shape {
private:
	double Leng, Angle;
public:
    Rhombus(double leng, double angle);
	double get_agnle();
	double get_leng();
    friend std::ostream& operator<<(std::ostream& os, const Rhombus& tr)
    {
        os << "Rhombus(" << tr.cord << ";"
           << tr.cord + tr.point[0] << ";" << tr.cord + tr.point[1]
           << ";" << tr.cord + tr.point[2] << "):" << tr.color;
        return os;
    }
};
Rhombus::Rhombus(double leng, double angle)
{
    cord = Point(0, 0);
    point.push_back(Point(leng, 0));
    point.push_back(Point(leng * (cos(angle) + 1), leng * sin(angle)));
    point.push_back(Point(leng * cos(angle), leng * sin(angle)));
	this->Leng = leng;
	this->Angle = angle;
}
double Rhombus::get_agnle()
{
	return this->Angle;
}
double Rhombus::get_leng()
{
	return this->Leng;
}

//===Параллелограмм===
class Parallelogram : public Shape {
private:
	double Width, Height;
public:
    Parallelogram(double width, double height);
	double get_width();
	double get_heigth();
    friend std::ostream& operator<<(std::ostream& os, const Parallelogram& tr)
    {
        os << "Parallelogram(" << tr.cord << ";"
           << tr.cord + tr.point[0] << ";" << tr.cord + tr.point[1]
           << ";" << tr.cord + tr.point[2] << "):" << tr.color;
        return os;
    }
};
Parallelogram::Parallelogram(double width, double height)
{
    cord = Point(0, 0);
    point.push_back(Point(width, 0));
    point.push_back(Point(width, height));
    point.push_back(Point(0, height));
	this->Width = width;
	this->Height = height;
}
double Parallelogram::get_width()
{
	return this->Width;
}
double Parallelogram::get_heigth()
{
	return this->Height;
}