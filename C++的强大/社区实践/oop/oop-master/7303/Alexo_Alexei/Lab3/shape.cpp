#include "shape.h"
#include <time.h>
#include <stdlib.h>

int Shape::ID;

Shape::Shape(Color color, Point center) : color(color), center(center) {
        Local_ID = ++ID;
}

void Shape::setColor(Color color) {this->color = color;}
const Color Shape::getColor() const {return this->color;}
const Point &Shape::getCenter() const {
    return center;
}

void Shape::Move(Point newCenter) {
    for(int i = 0; i < points.size(); i++){
        Point p = points[i];
        double lenghtVec = sqrt(pow(p.getX() - center.getX(), 2) + pow(p.getY() - center.getY(), 2));
        Point vec = Point((p.getX() - center.getX()) / lenghtVec, (p.getY() - center.getY()) / lenghtVec);
        p.setX(newCenter.getX() + (lenghtVec * vec.getX()));
        p.setY(newCenter.getY() + (lenghtVec * vec.getY()));
        points[i] = p;
    }
    center = newCenter;
}

void Shape::Move(double distance) {
    Point newCenter = center;
    newCenter.setX(center.getX() + distance);
    newCenter.setY(center.getY() + distance);
    for(int i = 0; i < points.size(); i++){
        Point p = points[i];
        double lenghtVec = sqrt(pow(p.getX() - center.getX(), 2) + pow(p.getY() - center.getY(), 2));
        Point vec = Point((p.getX() - center.getX()) / lenghtVec, (p.getY() - center.getY()) / lenghtVec);
        p.setX(newCenter.getX() + (lenghtVec * vec.getX()));
        p.setY(newCenter.getY() + (lenghtVec * vec.getY()));
        points[i] = p;
    }
    center = newCenter;
}

void Shape::Rotate(int angle, int direction) {
    for(int i = 0; i < points.size(); i++){
        Point p = points[i];
        double coss = cos(angle * PI/180.0);
        double sinn = sin(angle * PI/180.0);
        double x = center.getX() + (p.getX() - center.getX()) * coss - direction * (p.getY() - center.getY()) * sinn;
        double y = center.getY() + (p.getY() - center.getY()) * coss + direction * (p.getX() - center.getX()) * sinn;
        p.setX(x);
        p.setY(y);
        points[i] = p;
    }
}

ostream& operator << (ostream &out,const Shape& shape){
    out << "Shape ID = " << shape.Local_ID << endl;
    out << "Color`s shape:" << shape.color.R << " " << shape.color.G << " " << shape.color.B << endl;
    out << "Center`s shape:(" << shape.center.getX() << "," << shape.center.getY() << ")" << endl;
    return out;
}
