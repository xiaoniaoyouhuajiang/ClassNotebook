//
// Created by Максим Бачинский on 27.03.17.
//

#ifndef OOPFIGURES_FIGURE_CPP
#define OOPFIGURES_FIGURE_CPP

#include "Shape.h"

Shape::Shape(const Point &center, const Color &color) : center(center), color(color) {}

Shape::~Shape() {}


Point Shape::getCenter() const {
    return center;
}

Color Shape::getColor() const {
    return color;
}

std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    os << "center: " << shape.center << " color: " << shape.color;
    return os;
}

void Shape::changeLocation(double dx, double dy) {
    center.x = center.x + dx;
    center.y = center.x + dy;
}

void Shape::setColor(const Color &color) {
    this->color = color;
}

bool Shape::isUnionOf(const Shape &s1, const Shape &s2) {
    if (s2.isShapeInside(s1)) {
        return this->isEqualTo(s1);
    } else if (s1.isShapeInside(s2)) {
        return this->isEqualTo(s2);
    } else {
        return false;
    }
}

double Shape::triangleSquare(const Point &p1, const Point &p2, const Point &p3) {
    double a = lineLength(p1, p2);
    double b = lineLength(p1, p3);
    double c = lineLength(p2, p3);
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Shape::lineLength(const Point &p1, const Point &p2){
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

double Shape::toRadians(double angle) {
    return angle / 180 * M_PI;
}

#endif
