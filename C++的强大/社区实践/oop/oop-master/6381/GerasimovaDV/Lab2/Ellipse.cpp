#include "Ellipse.h"


Ellipse::Ellipse(Point* center, float R1, float R2, Color* color, int id) : Shape(color, id){
    points.push_back(new Point(center->x() + R2, center->y()));
    points.push_back(new Point(center->x() - R2, center->y()));
    points.push_back((new Point(center->x(), center->y() + R1)));
    points.push_back((new Point(center->x(), center->y() - R1)));
}

Point* Ellipse::getCenterPoint() {
    return new Point((points[0]->x()+points[1]->x())/2, (points[2]->y()+points[3]->y())/2);
}

float Ellipse::area() {
    return M_PI * (fabs(getCenterPoint()->x() - points[0]->x())) * fabs(getCenterPoint()->y() - points[2]->y());
}