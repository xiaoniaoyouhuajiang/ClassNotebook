//
// Created by 1 on 20.02.2019.
//

#ifndef SHAPE_SHAPE_H
#define SHAPE_SHAPE_H
#include "Color.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include "cmath"
#define PI 3.14159265

using namespace std;

class Shape{
public:
    Shape(Color color,Point center);
    void setColor(Color color);
    const Color getColor() const;
    const Point &getCenter() const;
    void Moving(Point newCenter);
    void Rotate(int angle,int direction);

    virtual void Scale(double coefficient){
        for(int i=0;i<points.size();i++){
            Point p=points[i];
            double lenghtVec=sqrt(pow(p.getX()-center.getX(),2)+pow(p.getY()-center.getY(),2));
            Point vec=Point((p.getX()-center.getX())/lenghtVec,(p.getY()-center.getY())/lenghtVec);
            lenghtVec=lenghtVec*coefficient;
            p.setX(center.getX()+(lenghtVec*vec.getX()));
            p.setY(center.getY()+(lenghtVec*vec.getY()));
            points[i]=p;
        }
    };

    friend ostream &operator<<(ostream &out, const Shape& shape);

private:
    Color color;
    int ID;

protected:
    Point center;
    vector<Point> points;
};
#endif //SHAPE_SHAPE_H
