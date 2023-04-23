//
// Created by 1 on 22.02.2019.
//

#ifndef SHAPE_ELLIPSE_H
#define SHAPE_ELLIPSE_H

#include <vector>
#include "Shape.h"

class Ellipse: public Shape{
public:
    Ellipse(Color color,Point center,double smallRadius,double bigRadius);
    void Scale(double coefficient) override;
    friend ostream &operator<<(ostream &out, const Ellipse& ellipse);

private:
    double smallRadius;
    double bigRadius;
};
#endif //SHAPE_ELLIPSE_H
