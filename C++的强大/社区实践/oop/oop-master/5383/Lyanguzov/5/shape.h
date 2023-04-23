#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>

// для 5 лабораторной работы
#include<random>
#include <functional>

#include "point.h"

//class Ellipse;
//class Arc;
//class Round;

const double eps = 0.0001;
const double epsStep = eps / 10;


// для 5 лабораторной
const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
static const int magicborder = 1 << 8;


struct Color
{
    size_t red;
    size_t green;
    size_t blue;

    Color(size_t r = 0, size_t g = 0, size_t b = 0) :
        red(r), green(g), blue(b) {}
};

class Shape
{
private:
    static unsigned int counter;


protected:
    const unsigned int id;
    Point center_coordinates;
    double current_angle;
    double current_scale;
    Color current_color;

    Shape(double x, double y, double angle = 0, double scale = 1, Color color = Color(0, 0, 0)) :
        id(counter++),
        current_angle(angle),
        current_scale(scale),
        current_color(color)
    {
        center_coordinates.x = x;
        center_coordinates.y = y;
    }

public:
    virtual ~Shape(){}
    void setColor(Color color);
    Color getColor() const;
    Point getPosition() const;
    void setPosition(Point p);
    double getAngle() const;
    void setAngle(double angle);
    unsigned int getId() const;

    virtual void scale(double scale) = 0;
    virtual double getPerimetr() const = 0;
    virtual double getArea() = 0;

    bool operator == (Shape &other);

    bool operator > (Shape &other);
    bool operator < (Shape &other);

    friend std::ostream &operator << (std::ostream &os, Shape &f);

    virtual bool isPointOnBorder(const Point &p) const = 0;

    virtual void print(std::ostream &os) = 0;

    // метод для вычисления количества точек пересечения фигур
    virtual int intersect(Shape& s2) const = 0;

    // создает случайную фигуру
    static Shape* createRandomShape();
};

class Arc : public Shape
{
protected:
    double startAngle;
    double finishAngle;
    double radius;
public:
    Arc(double x, double y, double startAngle, double finishAngle, double radius, double angle = 0, double scale = 1, Color color = Color(0, 0, 0))
        : Shape(x, y, angle, scale, color), startAngle(startAngle), finishAngle(finishAngle), radius(radius){}
    virtual ~Arc() {}
    void scale(double scale) override;
    double getPerimetr() const override;
    double getArea() override;

    int intersect(Shape &s2) const override;

    void print(std::ostream &os) override;

    bool isPointOnBorder(const Point &p) const override;

    bool match(const Arc &other) const;

    static Arc* createRandomShape();
};


class Round : public Arc
{
public:
    Round(double x, double y, double radius, double angle = 0, double scale = 1, Color color = Color(0, 0, 0))
        : Arc(x, y, -M_PI, M_PI, radius, angle, scale, color){}
    virtual ~Round(){}

    double getPerimetr() const override;
    double getArea() override;

    void print(std::ostream &os) override;

    bool isPointOnBorder(const Point &p) const override;

    static Round* createRandomShape();
};


class Ellipse : public Shape
{
protected:
    double aHalfAxis;
    double bHalfAxis;
public:
    Ellipse(double x, double y, double aHalfAxis, double bHalfAxis, double angle = 0, double scale = 1, Color color = Color(0, 0, 0))
        : Shape(x, y, angle, scale, color), aHalfAxis(aHalfAxis), bHalfAxis(bHalfAxis){}
    virtual ~Ellipse() {}
    void setAxis(std::pair<double, double> p);
    std::pair<double, double> getAxis();


    void scale(double scale) override;
    double getPerimetr() const  override;
    double getArea() override;

    int intersect(Shape &s2) const override;

    void print(std::ostream &os) override;

    bool isPointOnBorder(const Point &p) const override;

    bool match(const Ellipse& e) const;

    static Ellipse* createRandomShape();
};


#endif // SHAPE_H
