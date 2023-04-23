//
// Created by Максим Бачинский on 27.03.17.
//

#ifndef OOPFIGURES_PENTANGLE_H
#define OOPFIGURES_PENTANGLE_H


#include "Shape.h"
using namespace std;

class Pentangle : public Shape {
protected:
    vector<Point> points;
    const int ANGLE_QUANITY = 5;
public:
    Pentangle(const Point &p1, const Point &p2, const Point &p3, const Point &p4, const Point &p5, const Color &color);

    Pentangle(const Color &color);

    void rotate(double angle) override;

    void scale(double k) override;

    friend ostream &operator<<(ostream &os, const Pentangle &pentangle);

    void changeLocation(double dx, double dy) override;

    virtual bool isPointInside(const Point &p) const override;

    virtual bool isShapeInside(const Shape &f) const override;

    virtual double getSquare() const;

    double countSquareForPoint(const Point &p) const;

protected:
    virtual bool isEqualTo(const Shape &f) override;


};


#endif //OOPFIGURES_PENTANGLE_H
