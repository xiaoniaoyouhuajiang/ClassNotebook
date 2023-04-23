#pragma once
#include <shape.h>


class Square: public Shape{
public:
    Square(const Point& p, double side);

    friend std::ostream& operator<< (std::ostream& out, const Square& square);


};
