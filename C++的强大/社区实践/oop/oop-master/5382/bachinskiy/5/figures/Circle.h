//
// Created by Максим Бачинский on 27.03.17.
//

#ifndef OOPFIGURES_CIRCLE_H
#define OOPFIGURES_CIRCLE_H


#include "Shape.h"

class Circle : public Shape {
private:
    double radius = 0;

    void rotate(double angle) override;

public:
    Circle(double radius, const Point &center, const Color &color);

    void setRadius(double radius);

    void scale(double k) override;

    double getRadius();

    friend std::ostream &operator<<(std::ostream &os, const Circle &circle);

    virtual bool isPointInside(const Point &p) const override;

    virtual bool isShapeInside(const Shape &f) const override;

    virtual bool isEqualTo(const Shape &f) override;
};


#endif //OOPFIGURES_CIRCLE_H
