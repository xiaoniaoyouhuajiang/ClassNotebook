//
// Created by Максим Бачинский on 27.03.17.
//

#include "Pentangle.h"

Pentangle::Pentangle(const Point &p1, const Point &p2,
                     const Point &p3, const Point &p4, const Point &p5, const Color &color) : Pentangle(color) {
    vector<Point> pointArray = {p1, p2, p3, p4, p5};
    double centerX = (p1.x + p2.x + p3.x + p4.x + p5.x) / ANGLE_QUANITY;
    double centerY = (p1.y + p2.y + p3.y + p4.y + p5.y) / ANGLE_QUANITY;
    center = Point(centerX, centerY);

    pointArray.erase(std::unique(pointArray.begin(), pointArray.end()), pointArray.end());

    if (pointArray.size() != ANGLE_QUANITY) {
        throw std::invalid_argument("В пятиугольнике точки должны быть разными");
    }
    this->points = pointArray;
}

void Pentangle::rotate(double angle) {
    double angleInRadius = toRadians(angle);
    for (int i = 0; i < points.size(); i++) {
        double a = points[i].x;
        double b = points[i].y;
        points[i].x = a * cos(angleInRadius) - b * sin(angleInRadius);
        points[i].y = a * sin(angleInRadius) + b * cos(angleInRadius);
    }
}

void Pentangle::scale(double k) {
    if (k > 0) {
        for (int i = 1; i < ANGLE_QUANITY; i++) {
            points[i].x = points[0].x + fabs(points[i].x - points[0].x) * k;
            points[i].y = points[0].y + fabs(points[i].y - points[0].y) * k;
        }
    } else {
        throw std::invalid_argument("Коэфициент умножения должен быть больше нуля \n");
    }
}


Pentangle::Pentangle(const Color &color) :
        Shape(Point(0, 0), color), points{Point(0, 0), Point(1, 0), Point(2, 1), Point(2, 2), Point(1, 1)} {
}

ostream &operator<<(ostream &os, const Pentangle &pentangle) {
    os << static_cast<const Shape &>(pentangle) << " points: ";
    for (int i = 0; i < pentangle.points.size(); ++i) {
        os << pentangle.points[i] << " ";
    }
    return os;
}

void Pentangle::changeLocation(double dx, double dy) {
    Shape::changeLocation(dx, dy);
    for (int i = 0; i < points.size(); ++i) {
        points[i].x += dx;
        points[i].y += dy;

    }
}

bool Pentangle::isPointInside(const Point &p) const {
    double square = this->getSquare();
    double thisSquare = countSquareForPoint(p);
    double ds = fabs(square - thisSquare);
    return ds < square*0.01;

}

bool Pentangle::isShapeInside(const Shape &f) const {
    for (int i = 0; i < points.size(); ++i) {
        if (!f.isPointInside(points[i])) {
            return false;
        }
    }
    return true;
}

bool Pentangle::isEqualTo(const Shape &f) {
    const Pentangle* p = dynamic_cast<const Pentangle*>(&f);
    if (p) {
        vector<Point> p1(points);
        vector<Point> p2(p->points);
        std::sort(p1.begin(), p1.end());
        std::sort(p2.begin(), p2.end());
        return std::equal(p1.begin(), p1.end(), p2.begin());
    } else {
        return false;
    }
}

double Pentangle::getSquare() const {
    return countSquareForPoint(center);
}

double Pentangle::countSquareForPoint(const Point &p) const {
    double S = triangleSquare(p, points[0], points[ANGLE_QUANITY - 1]);
    for (int i = 0; i < ANGLE_QUANITY - 1; ++i) {
        S = S + triangleSquare(p, points[i], points[i + 1]);
    }
    return S;
}
