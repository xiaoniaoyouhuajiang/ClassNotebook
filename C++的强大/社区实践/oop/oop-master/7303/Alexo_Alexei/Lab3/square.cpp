#include "square.h"
#include <math.h>
#include <time.h>
#define PI 3.14

Square::Square(Color color, Point center, double length):Shape(color, center), lenght(length) {
    points.insert(points.end(), Point(center.getX() - length / 2, center.getY() - length / 2));
    points.insert(points.end(), Point(center.getX() + length / 2, center.getY() - length / 2));
    points.insert(points.end(), Point(center.getX() + length / 2, center.getY() + length / 2));
    points.insert(points.end(), Point(center.getX() - length / 2, center.getY() + length / 2));
}

void Square::Scale(double coefficient) {
    Shape::Scale(coefficient);
    lenght = sqrt(pow(points[0].getX() - points[1].getX(), 2) + pow(points[0].getY() - points[1].getY(), 2));
}

ostream &operator << (ostream &out, const Square& square){
    out << (Shape)square;
    out << "Left-Up point`s square:(" << square.points[0].getX() << "," << square.points[0].getY() << ")" << endl;
    out << "Lenght`s square:" << square.lenght << endl;
    return out;
}
