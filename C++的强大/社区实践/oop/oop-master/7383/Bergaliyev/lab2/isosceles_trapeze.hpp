#pragma once
#include "shape.hpp"
#include "trapeze.hpp"
#include <iostream>

class Isosceles_Trapeze : public Trapeze {
public:
    Isosceles_Trapeze(Color color, Point v1, Point v2, Point v3, Point v4);
    std::ostream & print(std::ostream & ostream) const;
};
