#ifndef ARC_H
#define ARC_H
#include "shape.h"
#include "ellipse.h"

class Arc : public Shape
{
protected:
    double startAngle;
    double finishAngle;
    double radius;
public:
    Arc(double x, double y, double startAngle, double finishAngle, double radius, double angle = 0, double scale = 1, Color color = Color(0, 0, 0))
        : Shape(x, y, angle, scale, color), startAngle(startAngle), finishAngle(finishAngle), radius(radius){}
    virtual ~Arc() {}
    void scale(double scale) override;
    double getPerimetr() const override;
    double getArea() override;

    int intersect(Shape &s2) const override;

    void print(std::ostream &os) override;

    bool isPointOnBorder(const Point &p) const override;

    bool match(const Arc &other) const;
};

#endif // ARC_H
