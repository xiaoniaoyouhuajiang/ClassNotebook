#include "Point.h"

Point::Point(float x, float y) : x_point(x), y_point(y) {}

float& Point::x() {
    return x_point;
}

float& Point::y() {
    return y_point;
}
