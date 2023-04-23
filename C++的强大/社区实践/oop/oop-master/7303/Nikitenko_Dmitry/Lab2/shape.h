#ifndef SHAPE_H
#define SHAPE_H
#include "coor.h"
#include "color.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

class Shape
{
public:
    Shape();
    Shape(Coor, Color, double angle);
    Shape(double,double,Color, double angle = 0);

    void moveTo(Coor);
    void moveTo(double x,double y);
    virtual void scale(double) = 0;
    void setColor(Color color);
    Color getColor(){return _color;}
    Coor getCenter(){return _center;}
    friend std::ostream& operator<< (std::ostream &out, Shape&);
    virtual std::ostream& print(std::ostream&) = 0;
    virtual ~Shape(){--id;}
    void rotate(double);
    virtual void updateCoords() = 0;
    unsigned long int getID(){return id;}
    void angle(double angle){_angle = angle;}
    double angle(){return _angle;}
protected:
    unsigned long int id;
    double _angle;
    Coor _center;
    Color _color;
    std::vector<Coor> coords;



};

#endif // SHAPE_H
