#include "Parallelogram.h"

Parallelogram::Parallelogram(Point* p1, Point* p2, Point* p3, Color* color, int id) : Shape(color, id) {
    points.push_back(new Point(p1->x(), p1->y()));
    points.push_back(new Point(p2->x(), p2->y()));
    points.push_back(new Point(p3->x(), p3->y()));
    Point* center = new Point((p1->x()+p3->x())/2, (p1->y()+p3->y())/2);
    points.push_back(new Point(2*center->x() - p2->x(), 2*center->y() - p2->y()));
}

Point* Parallelogram::getCenterPoint() {
    return new Point((points[0]->x()+points[2]->x())/2, (points[0]->y()+points[2]->y())/2);
}

float Parallelogram::area() {
    return fabs(points[0]->x() - points[1]->x()) * fabs(points[0]->y() - points[2]->y());
}