#ifndef OOP_POINT_H
#define OOP_POINT_H

#include <cmath>

class Point {
public:
    Point(float x, float y);

    float& x();

    float& y();

private:
    float x_point;
    float y_point;
};


#endif //OOP_POINT_H
