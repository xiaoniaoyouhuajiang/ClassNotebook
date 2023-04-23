

#include "iostream"
#include "figure.h"
#include "point.h"
#ifndef Ellipse_h
#define Ellipse_h
class Ellipse : public Shape
{
protected :
    Point center;
    double a;
    double b;
    
public:
    
    Ellipse(const Point &center, double a,double b, double fi);
    void move_to(const Point &p) override;
    void scale(double scale = 1) override;
    void rotate (double angle) override;
    void print (std::ostream &os) const override;
    
    std::vector<Point> getVertices() const override;
};

#endif /* Ellipse_h */
