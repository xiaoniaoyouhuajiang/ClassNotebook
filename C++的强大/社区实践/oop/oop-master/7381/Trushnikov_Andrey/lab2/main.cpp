#include <iostream>
#include <shape.h>
#include <circle.h>
#include "parallelogram.h"
#include "hexagon.h"
using namespace std;

int main(){
    /*
    Point point;
    double r = 10;
    std::vector <Point> coords = {{0,0},{2,4},{10,4},{8,0}};
    Colour colour(10,20,30);
    Parallelogram par(colour,coords);
    Circle circle(point,r,colour);
    std::cout << par;
    std::cout << circle;

    par.scale(2);
    std::cout << par;
    */
    Point point(2,2);
    Colour colour(10,20,30);
    std::vector <Point> coords = {{1,5},{3,10},{8,10},{10,5},{3,1},{8,1}};
    Hexagon hex(colour,coords,3,4);
    hex.print(std::cout);
    hex.move(point);
    hex.print(std::cout);


    return 0;
}
