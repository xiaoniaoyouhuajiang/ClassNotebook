#pragma once
#include <shape.h>


class isoscelesTriangle:public Shape{
public:
    isoscelesTriangle(const Point& p1, const Point& p2, const Point& p3);

    friend std::ostream& operator<< (std::ostream& out, const isoscelesTriangle& iTr);

protected:
    std::vector<int> sides;
};
