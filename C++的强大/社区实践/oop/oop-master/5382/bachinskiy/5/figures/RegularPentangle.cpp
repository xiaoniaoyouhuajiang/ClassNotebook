//
// Created by Максим Бачинский on 27.03.17.
//

#include "RegularPentangle.h"

double RegularPentangle::getRadius() const {
    return radius;
}

RegularPentangle::RegularPentangle(const Point &center, const Point &point, const Color &color) : Pentangle(color) {
    this->center = center;
    this->radius = sqrt(pow((point.x - center.x), 2) + pow((point.y - center.y), 2));
    double angleInRadius = toRadians(360 / ANGLE_QUANITY);
    std::vector<Point> pointArray;
    pointArray.push_back(point);
    for (int i = 1; i < ANGLE_QUANITY; i++) {
        double a = pointArray[i - 1].x - center.x;
        double b = pointArray[i - 1].y - center.y;
        double x = a * cos(angleInRadius) - b * sin(angleInRadius) + center.x;
        double y = a * sin(angleInRadius) + b * cos(angleInRadius) + center.y;
        pointArray.push_back(Point(x, y));
    }
    this->points = pointArray;
}
