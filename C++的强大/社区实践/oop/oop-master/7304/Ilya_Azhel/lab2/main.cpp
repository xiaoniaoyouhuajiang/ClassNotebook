#include "square.hpp"
#include "trapeze.hpp"
#include "isosceles_trapeze.hpp"
#include <cmath>

int main(){
    Color color(255, 255, 255);
    Point center(0, 0);
    Point v(-3, -4);
    Square a(color, Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    std::cout << a;
    a.rotate(0.25*M_PI);
    std::cout << a;
    a.relocate(Point(2, 3));
    std::cout << a;
    Trapeze b(color, Point(1, 0), Point(2, 0), Point(0, 7), Point(9, 7));
    b.relocate(Point(1, 1));
    std::cout << b;
    b.rotate(1.5*M_PI);
    std::cout << b;
    Isosceles_Trapeze d(color, Point(-4, -4), Point(2, 2), Point(-2, 2), Point(4, -4));
    d.rotate(M_PI/2);
    std::cout << d;
    d.scale(0.25);
    std::cout << d;
    return 0;
}
