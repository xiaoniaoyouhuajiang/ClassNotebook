#ifndef POINT_H
#define POINT_H


class Point2D
{
public:
    Point2D();
    Point2D(int x, int y);
    ~Point2D() = default;

    Point2D* clone();

public:
    int x;
    int y;
};

#endif // POINT_H
