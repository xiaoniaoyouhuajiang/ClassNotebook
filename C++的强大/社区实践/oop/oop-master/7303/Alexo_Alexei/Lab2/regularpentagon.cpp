#include "regularpentagon.h"
#include <time.h>

RegularPentagon::RegularPentagon(Color color, Point center, int length):Shape(color, center), lenght(length) {
    double R = sqrt((50 + 10 * sqrt(5)) / 10) * length;
    points.insert(points.end(), Point(center.getX() + R * cos(54 * PI / 180.0), center.getY() + R * sin(54 * PI / 180.0)));
    points.insert(points.end(), Point(center.getX() + R * cos(126 * PI / 180.0),center.getY() + R * sin(126 * PI / 180.0)));
    points.insert(points.end(), Point(center.getX() + R * cos(198 * PI / 180.0), center.getY() + R * sin(198 * PI / 180.0)));
    points.insert(points.end(), Point(center.getX() + R * cos(270 * PI / 180.0), center.getY() + R * sin(270 * PI / 180.0)));
    points.insert(points.end(), Point(center.getX() + R * cos(342 * PI/180.0), center.getY() + R * sin(342 * PI / 180.0)));
}

void RegularPentagon::Scale(double coefficient) {
    Shape::Scale(coefficient);
    lenght = sqrt(pow(points[0].getX() - points[1].getX(), 2) + pow(points[0].getY() - points[1].getY(), 2));
}

ostream &operator<<(ostream &out, const RegularPentagon& regularPentagon) {
    out << (Shape)regularPentagon;
    out << "point`s RegularPentagon:" << endl;
    for(int i = 0; i < regularPentagon.points.size(); i++)
        out << "   (" << regularPentagon.points[i].getX() << "," << regularPentagon.points[i].getY() << ")" << endl;
    out << "Length`s RegularPentagon:" << regularPentagon.lenght << endl;
    return out;
}
