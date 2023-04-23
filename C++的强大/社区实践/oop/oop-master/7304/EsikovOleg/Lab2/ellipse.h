#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
protected:
    Point LeftFocus;
    Point RightFocus;
    double length;  // |MF1| + |MF2| = const = 2a = length!

public:
    Ellipse(Point LF, Point RF, double space);
    ~Ellipse(){}

    void Turn(double value);
    void toScale(double k);
    void Moving(Point dot);
    void info(ostream& os);
};

#endif // ELLIPSE_H
