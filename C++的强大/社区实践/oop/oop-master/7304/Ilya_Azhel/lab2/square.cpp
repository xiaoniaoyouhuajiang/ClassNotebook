#include "square.hpp"

Square::Square(Color color, Point v1, Point v2, Point v3, Point v4) : Isosceles_Trapeze(color, v1, v2, v3, v4){
    if(std::abs(v1.distance(v2) - v3.distance(v4)) > eps)
	throw std::invalid_argument("Vertices don't compose a square");
}
     
std::ostream & Square::print(std::ostream & ostream) const {
    return ostream << "Square ";
}
