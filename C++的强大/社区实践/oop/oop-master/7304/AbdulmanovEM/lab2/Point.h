//
// Created by 1 on 20.02.2019.
//

#ifndef SHAPE_POINT_H
#define SHAPE_POINT_H
class Point{
public:
    Point(double x, double y);
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);

private:
    double x;
    double y;
};
#endif //SHAPE_POINT_H
