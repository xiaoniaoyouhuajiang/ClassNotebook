#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle
{
public:
    Square() : Rectangle() {}
    Square(const Point2d& vertex, double side, double angle = 0) : Rectangle(vertex, side, side, angle) {}
    Square(double random_range);

protected:
    void print(std::ostream &os) const override;
};

#endif // SQUARE_H
