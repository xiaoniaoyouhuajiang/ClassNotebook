#include <iostream>
#include "shape.h"
int main() {
    
    Triangle tr(Point(0,0),Point(0,1),Point(1,0));

    std::cout<<tr;
    tr.rotate(180);
    std::cout<<tr;
    tr.scale(2);
    std::cout<<tr;
    tr.move(Point(1,1));
    tr.setColor(Color(2,2,2));
    std::cout<<tr;

    RegPentagon pent(Point(0,0),5);
    std::cout<<pent<<std::endl;
    return 0;
}