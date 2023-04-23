#include <iostream>

#include "shape.h"
#include "star.h"
#include "ellipse.h"
#include "sector.h"


int main()
{
    Sector  a(10, 10, 90,  Color(255, 0, 0), 10, 90);
    Star    s(100, 100, 0, Color(0,0,0), 50,10)     ;
    Ellipse e(50, 250, 90, Color(0, 255, 0), 10, 10);
    Ellipse q(50, 250, 90, Color(0, 255, 0), 10, 10);
    Sector  b;

    b = a;
    b.setCoordinates(50,50);
    b.rotate(45);
    b.scale(0.5);
    b.setColor(Color(0, 0, 0));

    std::cout << a << s << e << b;
    s.rotate(180);

    std::cout<<(s++);
    std::cout<<(++s);  
    std::cout<<(q);
    return 0;
}

