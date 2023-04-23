#ifndef ROUND_H
#define ROUND_H
#include "arc.h"

class Round : public Arc
{
public:
    Round(double x, double y, double radius, double angle = 0, double scale = 1, Color color = Color(0, 0, 0))
        : Arc(x, y, -M_PI, M_PI, radius, angle, scale, color){}
    virtual ~Round(){}

    double getPerimetr() const override;
    double getArea() override;

    void print(std::ostream &os) override;

    bool isPointOnBorder(const Point &p) const override;
};

#endif // ROUND_H
