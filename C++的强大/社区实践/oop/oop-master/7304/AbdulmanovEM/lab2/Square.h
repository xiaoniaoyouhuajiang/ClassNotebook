//
// Created by 1 on 20.02.2019.
//

#ifndef SHAPE_SQUARE_H
#define SHAPE_SQUARE_H

#include "Point.h"
#include "Shape.h"
#include <vector>
using namespace std;

class Square:public Shape{
public:
    Square(Color color, Point center, double lenght);
    void Scale(double coefficient) override;
    friend ostream &operator<<(ostream &out, const Square& square);
private:
    double lenght;
};
#endif //SHAPE_SQUARE_H
