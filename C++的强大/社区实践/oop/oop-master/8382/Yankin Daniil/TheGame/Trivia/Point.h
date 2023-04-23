#pragma once

#include <cstdint>


class Point {
private:
    uint16_t x;
    uint16_t y;

public:
    Point(uint16_t x, uint16_t y);
    ~Point();

    uint16_t getX() const;
    uint16_t getY() const;

    friend bool operator==(const Point& one, const Point& two);
    friend bool operator!=(const Point& one, const Point& two);
    friend bool operator<(const Point& one, const Point& two);

    static Point generatePoint(uint16_t minX, uint16_t maxX, uint16_t minY, uint16_t maxY);
};
