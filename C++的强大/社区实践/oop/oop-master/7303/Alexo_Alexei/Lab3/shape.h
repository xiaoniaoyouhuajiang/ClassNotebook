#ifndef SHAPE_H
#define SHAPE_H

#include "color.h"
#include "point.h"
#include <iostream>
#include <vector>
#include "cmath"
#define PI 3.14

using namespace std;

class Shape{
public:

    static int ID;

    Shape(Color color, Point center);
    void setColor(Color color);
    const Color getColor() const;
    const Point &getCenter() const;
    void Move(Point newCenter);
    void Move(double distance);
    void Rotate(int angle,int direction);

    virtual void Print() {
        std::cout << "Shape ID = " << Local_ID << endl;
        std::cout << "Color`s shape:" << color.R << " " << color.G << " " << color.B << endl;
        std::cout << "Center`s shape:(" << center.getX() << "," << center.getY() << ")" << endl;
    }

    virtual void Scale(double coefficient){
        for(int i = 0; i < points.size(); i++){
            Point p = points[i];
            double lengthVec = sqrt(pow(p.getX() - center.getX(), 2) + pow(p.getY() - center.getY(), 2));
            Point vec = Point((p.getX() - center.getX()) / lengthVec, (p.getY() - center.getY()) / lengthVec);
            lengthVec = lengthVec * coefficient;
            p.setX(center.getX() + (lengthVec * vec.getX()));
            p.setY(center.getY() + (lengthVec * vec.getY()));
            points[i] = p;
        }
    };

    friend ostream &operator << (ostream &out, const Shape& shape);

private:
    Color color;

protected:
    int Local_ID;
    Point center;
    vector<Point> points;
};

#endif // SHAPE_H
