
#include "Point.h"

Point::Point(int x, int y) {

    this->x = x;
    this->y = y;

}

Point::Point() {

    x = 0;
    y = 0;

}

bool Point::operator!=(Point &other) const {
    return x != other.x || y != other.y;
}

bool Point::operator==(Point &other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(Point other) const {
    return x != other.x || y != other.y;
}

bool Point::operator==(Point other) const {
    return x == other.x && y == other.y;
}