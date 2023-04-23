//
// Created by user on 31.03.19.
//

#ifndef OOP_2_SHAPE_H
#define OOP_2_SHAPE_H
#include "Color.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include "cmath"

using namespace std;


class Shape {

protected:
    Color color;
    unsigned long int id;
    Point center;
    vector <Point> points;

public:
    Shape(Point center,Color color );
    void set_color(Color color);
    Color get_color() const ;
    unsigned long int get_id() const;
    void moving(Point p);
    void rotation(double grade);
    virtual void scaling(double k)=0;
    friend std::ostream& operator << (ostream& stream, Shape& shape);
    Shape &operator+(const double ch);

};

#endif //OOP_2_SHAPE_H
