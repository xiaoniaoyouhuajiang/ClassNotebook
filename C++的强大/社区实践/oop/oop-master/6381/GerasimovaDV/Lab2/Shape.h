#ifndef OOP_SHAPE_H
#define OOP_SHAPE_H

#include "Point.h"
#include "Color.h"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Shape {
public:
    explicit Shape(Color* color, int id) : color(color), id(id) {};

    void move(Point* point);

    void rotate(float angle);

    void scale(float factor);

    Color* getColor() const;

    int getId() const;

    vector<Point*>& getPoints();

    virtual Point* getCenterPoint() = 0;

    virtual float area() = 0;

    virtual ostream& printShape(ostream& stream, Shape& figure) const = 0;

    friend ostream& operator<<(ostream& stream, Shape& figure) {
        return figure.printShape(stream, figure);
    };

protected:
    vector<Point*> points;
    Color* color;
    int id;
};


#endif //OOP_SHAPE_H
