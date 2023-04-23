#include "Point.h"
#include <cstdlib>
#include <ctime>


Point::Point(uint16_t x, uint16_t y) : x(x), y(y) {};

Point::~Point() {};


uint16_t Point::getX() const {
    return x;
}
uint16_t Point::getY() const {
    return y;
}


bool operator==(const Point& one, const Point& two) {
    if (one.x == two.x && one.y == two.y)
        return true;
    return false;
}

bool operator!=(const Point& one, const Point& two) {
    return !(one == two);
}

bool operator<(const Point& one, const Point& two) {
    if (one.y < two.y)
        return true;
    if (one.x < two.x)
        return true;
    return false;
}


Point Point::generatePoint(uint16_t minX, uint16_t maxX, uint16_t minY, uint16_t maxY) {
    // minX <= randX < maxX
    // minY <= randY < maxY
    uint16_t randX = rand() % (maxX - minX) + minX;
    uint16_t randY = rand() % (maxY - minY) + minY;
    return Point(randX, randY);
}
