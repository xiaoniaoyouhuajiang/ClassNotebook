#pragma once
#include "shape.hpp"

class Trapeze : public Shape {
public:
    Trapeze(Color color, Point v1, Point v2, Point v3, Point v4);
    std::ostream & print(std::ostream & ostream) const;
};
