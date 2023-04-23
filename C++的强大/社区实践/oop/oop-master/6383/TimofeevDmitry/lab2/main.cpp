// Timofeev Dmitry № 17 var 6
// Треугольник, ромб, параллелограмм

#include <iostream>
#include <vector>
#include <cmath>
#include "Triangle.h"
#include "Rhomb.h"


int main() {
///////////////////////////////////////////////////////////
    Triangle t("green",Point(0,0),Point(3,0),Point(0,4));
    std::cout<<"triangle edges before transform: "
             << std::to_string(t.getAB())
             <<" "<<std::to_string(t.getBC())
             <<" "<<std::to_string(t.getAC()) <<"\n";
    t.translate(5,7);
    t.scale(10);
    t.rotate(M_PI/2);
    std::cout<<"triangle edges after transform: "
             << std::to_string(t.getAB())
             <<" "<<std::to_string(t.getBC())
             <<" "<<std::to_string(t.getAC()) <<"\n\n";

    std::cout<<t<<"\n";
///////////////////////////////////////////////////////////
    Parallelogram p("blue",M_PI/2,3,2);
    std::cout<<"Parallelogram edges before transform: "
             << std::to_string(p.getA()) <<" "<<std::to_string(p.getB()) <<"\n";
    p.scale(2);
    p.rotate(M_PI/6);
    p.translate(-1,1);
    std::cout<<"Parallelogram edges after transform: "
             << std::to_string(p.getA()) <<" "<<std::to_string(p.getB()) <<"\n\n";

    std::cout<<p<<"\n";
    ///////////////////////////////////////////////////////////
    Rhomb r("yellow",12,5);
    std::cout<<"Rhomb edges before transform: " <<std::to_string(r.getA()) <<"\n";
    r.translate(5,-9);
    r.rotate(M_PI/3);
    r.scale(10);
    std::cout<<"Rhomb edges after transform: " <<std::to_string(r.getA()) <<"\n\n";



    std::cout<<r<<"\n";
    ///////////////////////////////////////////////////////////
    return 0;
}