//
// Created by user on 31.03.19.
//

#ifndef OOP_2_FIVEPOINTEDSTAR_H
#define OOP_2_FIVEPOINTEDSTAR_H

#include "Shape.h"

class fivePointedStar : public Shape {
private:
    double radius;
    double angle;

public:
    fivePointedStar(Point center, Color color, double radius);
    void scaling(double k) override;
    friend std::ostream & operator << (std::ostream & out, fivePointedStar &fivePointedStar);
};


#endif //OOP_2_FIVEPOINTEDSTAR_H
