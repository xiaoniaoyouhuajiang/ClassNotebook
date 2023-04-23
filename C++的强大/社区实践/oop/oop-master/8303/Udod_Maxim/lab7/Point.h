//
// Created by shenk on 15.02.2020.
//

#ifndef UNTITLED13_POINT_H
#define UNTITLED13_POINT_H


class Point {

public:
    int x, y;

    Point();
    Point(int x, int y);

    bool operator!=(Point &other) const;
    bool operator!=(Point other) const;
    bool operator==(Point &other) const;
    bool operator==(Point other) const;


};


#endif //UNTITLED13_POINT_H
