#ifndef LONCHINA_POINT_H
#define LONCHINA_POINT_H


class Point {
public:
    double x;
    double y;
    Point() {
        this->x = 0;
        this->y = 0;
    }
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};


#endif //LONCHINA_POINT_H
