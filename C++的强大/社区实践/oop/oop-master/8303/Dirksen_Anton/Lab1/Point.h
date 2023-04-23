//
// Created by mensch on 02.03.2020.
//

#ifndef OOP_LABS_POINT_H
#define OOP_LABS_POINT_H


class Point {

public:
    int x, y;

    Point();
    Point(int x, int y);
    bool operator!=(Point &other) const
    {
        return x != other.x || y != other.y;
    }

    bool operator==(Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(Point other) const
    {
        return x != other.x || y != other.y;
    }

    bool operator==(Point other) const
    {
        return x == other.x && y == other.y;
    }
};


#endif //OOP_LABS_POINT_H
