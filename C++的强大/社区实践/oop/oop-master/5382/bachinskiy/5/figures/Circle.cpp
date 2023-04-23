//
// Created by Максим Бачинский on 27.03.17.
//

#include "Circle.h"

Circle::Circle(double radius, const Point &center, const Color &color) : Shape(center, color) {
    this->setRadius(radius);
}

void Circle::rotate(double angle) {}

void Circle::scale(double k) {
    if (k > 0) {
        radius = radius * k;
    } else {
        throw std::invalid_argument("Коэфициент умножения должен быть больше нуля \n");
    }
}

double Circle::getRadius() {
    return radius;
}

std::ostream &operator<<(std::ostream &os, const Circle &circle) {

    os << static_cast<const Shape &>(circle) << " radius: " << circle.radius;
    return os;
}

void Circle::setRadius(double radius) {
    if (radius > 0) {
        this->radius = radius;
    } else {
        throw std::invalid_argument("Радиус должен быть больше нуля \n");
    }
}

bool Circle::isPointInside(const Point &p) const {
    double l = pow(p.x - center.x, 2) + pow(p.y - center.y, 2);
    return l <= pow(radius, 2);
}

bool Circle::isShapeInside(const Shape &f) const {
    const int POINT_QUANITY = 64;
    double angleInRadians = toRadians(360/POINT_QUANITY);
    double c = cos(angleInRadians);
    double s = sin(angleInRadians);
    double x = center.x + radius;
    double y = center.y;
    double rx, ry;

    for (int i = 0; i < POINT_QUANITY; ++i) {
        if (!f.isPointInside(Point(x, y))) {
            return false;
        }
        rx = x - center.x;
        ry = y - center.y;
        x = center.x + rx * c - ry * s;
        y = center.y + rx * s + ry * c;
    }

    return true;
}

bool Circle::isEqualTo(const Shape &f) {
    const Circle* c = dynamic_cast<const Circle*>(&f);
    if (c) {
        return radius == c->radius && center == c->center;
    } else {
        return false;
    }
}