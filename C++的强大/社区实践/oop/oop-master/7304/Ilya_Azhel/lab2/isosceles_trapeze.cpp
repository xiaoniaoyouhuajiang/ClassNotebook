#include "isosceles_trapeze.hpp"

Isosceles_Trapeze::Isosceles_Trapeze(Color color, Point V1, Point V2, Point V3, Point V4) : Trapeze(color, V1, V2, V3, V4) {
    if(std::abs(v3.distance(v1) - v4.distance(v2)) > eps)
	throw std::invalid_argument("Vertexes don't compose a isosceles trapeze");
}

std::ostream & Isosceles_Trapeze::print(std::ostream & ostream) const{
    return ostream << "Isosceles Trapeze ";
}
