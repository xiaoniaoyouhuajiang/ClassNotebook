#include <iostream>
#include "square.h"
#include "star.h"
#include "pentagon.h"

int main(){

    Square square(Point(5,5), Color(255,255,255),10);
    std::cout<<square;
    square.Turn(45);
    std::cout<<square;
    square.Move(Point(10,10));
    std::cout<<square;
    square.Scale(2);
    std::cout<<square;

    Star star(Point(5,5), Color(255,255,255),10,15);
    std::cout<<star;
    star.Turn(45);
    std::cout<<star;
    star.Move(Point(10,10));
    std::cout<<star;
    star.Scale(2);
    std::cout<<star;  

    Pentagon pentagon(Point(5,5), Color(255,255,255),10);
    std::cout<<pentagon;
    pentagon.Turn(45);
    std::cout<<pentagon;
    pentagon.Move(Point(10,10));
    std::cout<<pentagon;
    pentagon.Scale(2);
    std::cout<<pentagon;

  return 0;
}
