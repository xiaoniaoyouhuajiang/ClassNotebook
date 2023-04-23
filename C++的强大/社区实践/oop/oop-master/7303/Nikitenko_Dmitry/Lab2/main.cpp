#include <iostream>
#include "ellipse.h"
#include "parall.h"
#include "sector.h"
int main()
{
    Color color(1,2,3);
    Coor center(0,0);
    Sector s(9,3,center,color,0);
    Ellipse e(0,0,10, 5, color,0);
    Parall p(4,3,30,0,0,color,0);
    Parall p2(2,3,4,5,5,color,2);
    std::cout<<"*****SECTOR*****"<<std::endl;
    std::cout<<s;
    s.rotate(180);
    std::cout<<s;
    s.scale(0.5);
    std::cout<<s;
    s.rotate(90);
    s.moveTo(5,2);
    std::cout<<s;
    std::cout<<"*****Ellipse*****"<<std::endl;
    std::cout<<e;
    e.rotate(180);
    std::cout<<e;
    e.scale(0.5);
    std::cout<<e;
    e.rotate(90);
    e.moveTo(5,2);
    std::cout<<e;
    std::cout<<"*****Parallelogram*****"<<std::endl;
    std::cout<<p;
    p.rotate(180);
    std::cout<<e;
    p.scale(0.5);
    std::cout<<p;
    p.rotate(90);
    p.moveTo(5,2);
    std::cout<<p;
    std::cout<<p2.getID();
    return 0;
}
