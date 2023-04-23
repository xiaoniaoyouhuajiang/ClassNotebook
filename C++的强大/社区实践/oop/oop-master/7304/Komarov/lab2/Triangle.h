//
// Created by user on 31.03.19.
//

#ifndef OOP_2_TRIANGLE_H
#define OOP_2_TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(Point center, Color color,double a, double b, double angle_a_b);

    void scaling(double k) override;
    friend std::ostream & operator << (std::ostream & out, Triangle &triangle);

protected:
    double a;
    double b;
    double angle_a_b;
    //this side compute by theorem of cos
    double c;
};



#endif //OOP_2_TRIANGLE_H
