#include "EllipseSector.h"

EllipseSector::EllipseSector(Point* center, float R1, float R2, float start_angle, float end_angle, Color* color,
                             int id) : Shape(color, id) {
    points.push_back(new Point(center->x(), center->y()));
    points.push_back(new Point(center->x() + R2 * cos(start_angle), center->y() + R1 * sin(start_angle)));
    points.push_back(new Point(center->x() + R2 * cos(end_angle), center->y() + R1 * sin(end_angle)));
    rad = fabs(start_angle - end_angle);
}

Point* EllipseSector::getCenterPoint() {
    return points[0];
}

float EllipseSector::area() {
    return rad / 2
           * sqrt(pow((getCenterPoint()->x() - points[1]->x()), 2) + pow((getCenterPoint()->y() - points[1]->y()), 2))
           * sqrt(pow((getCenterPoint()->x() - points[2]->x()), 2) + pow((getCenterPoint()->y() - points[2]->y()), 2));
}