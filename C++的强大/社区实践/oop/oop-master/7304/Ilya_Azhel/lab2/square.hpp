#pragma once
#include "shape.hpp"
#include "isosceles_trapeze.hpp"

class Square : public Isosceles_Trapeze {
public:
    Square(Color color, Point v1, Point v2, Point v3, Point v4);
    std::ostream & print(std::ostream & ostream) const;
};
