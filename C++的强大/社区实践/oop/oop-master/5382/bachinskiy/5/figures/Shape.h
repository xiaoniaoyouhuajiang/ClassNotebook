//
// Created by Максим Бачинский on 27.03.17.
//

#ifndef OOPFIGURES_FIGURE_H
#define OOPFIGURES_FIGURE_H

#include <iostream>
#include <math.h>
#include <vector>

struct Point {
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }

    bool operator==(const Point &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const Point &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Point &rhs) const {
        if (x < rhs.x)
            return true;
        if (rhs.x < x)
            return false;
        return y < rhs.y;
    }

    bool operator>(const Point &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Point &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Point &rhs) const {
        return !(*this < rhs);
    }
};

struct Color {
    int r = 0;
    int g = 0;
    int b = 0;

    Color(int r, int g, int b) {
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
            throw std::invalid_argument("Цвет должен находится в промежутке (0; 255)\n");
        } else {
            this->r = r;
            this->g = g;
            this->b = b;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &color) {
        os << "r: " << color.r << " g: " << color.g << " b: " << color.b;
        return os;
    }
};

class Shape {

protected:
    Point center;
    Color color;

    Shape(const Point &center, const Color &color);

    Shape(const Color &color);

    Shape();

    virtual void changeLocation(double dx, double dy);

    virtual void rotate(double angle) = 0;

    virtual void scale(double p) = 0;


    virtual bool isEqualTo(const Shape &f) = 0;

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

public:
    Point getCenter() const;

    Color getColor() const;

    void setColor(const Color &color);

    bool isUnionOf(const Shape &s1, const Shape &s2);

    virtual bool isPointInside(const Point &p) const = 0;

    virtual bool isShapeInside(const Shape &f) const = 0;

    static double triangleSquare(const Point &p1, const Point &p2, const Point &p3);

    static double lineLength(const Point &p1, const Point &p2);

    static double toRadians(double angle);

    virtual ~Shape();

};


#endif //OOPFIGURES_FIGURE_H
