#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"

class Ellipse : public Shape
{
protected:
    double aHalfAxis;
    double bHalfAxis;
public:
    Ellipse(double x, double y, double aHalfAxis, double bHalfAxis, double angle = 0, double scale = 1, Color color = Color(0, 0, 0))
        : Shape(x, y, angle, scale, color), aHalfAxis(aHalfAxis), bHalfAxis(bHalfAxis){}
    virtual ~Ellipse() {}
    void setAxis(std::pair<double, double> p);
    std::pair<double, double> getAxis();


    void scale(double scale) override;
    double getPerimetr() const  override;
    double getArea() override;

    int intersect(Shape &s2) const override;

    void print(std::ostream &os) override;

    bool isPointOnBorder(const Point &p) const override;

    bool match(const Ellipse& e) const;
};

#endif // ELLIPSE_H
