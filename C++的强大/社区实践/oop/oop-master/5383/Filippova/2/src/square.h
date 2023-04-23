
#ifndef Square_h
#define Square_h

#include "rectangle.h"
#include "iostream"
#include "figure.h"

using namespace std;

class Square : public Rectangle

{
public:
    Square(const Point &upperLeft, double side, double fi):
        Rectangle(upperLeft, side, side, fi) {}
};
#endif /* Square_h */
