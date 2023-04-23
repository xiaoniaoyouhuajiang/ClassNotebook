#pragma once
#include <shape.h>


class rightTriangle: public Shape{

public:
    rightTriangle(const Point& p, double kat1, double kat2);

    friend std::ostream& operator<< (std::ostream& out, const rightTriangle& rTr);

protected:
    std::vector<int> sides;
};

