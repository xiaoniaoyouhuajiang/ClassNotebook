#include "ellipse.h"
#include <cmath>
#define PI 3.14

Ellipse::Ellipse(Color color, Point center, double smallRadius, double bigRadius):Shape(color, center), smallRadius(smallRadius), bigRadius(bigRadius){
    for(int i = 0; i <= 360; i++)
        points.insert(points.end(), Point(center.getX() + bigRadius * cos(i * PI / 180.0), center.getY() + smallRadius * sin(i * PI / 180.0)));
}


void Ellipse::Scale(double coefficient) {
    Shape::Scale(coefficient);
    bigRadius = bigRadius * coefficient;
    smallRadius = smallRadius * coefficient;
}

ostream &operator << (ostream &out, const Ellipse& ellipse) {
    out << (Shape)ellipse;
    out << "point`s Left:";
    out << "(" << ellipse.points[0].getX() << "," << ellipse.points[0].getY() << ")" << endl;
    out << "BigRadius:" << ellipse.bigRadius << endl;
    out << "SmallRadius:" << ellipse.smallRadius << endl;
    return out;
}
