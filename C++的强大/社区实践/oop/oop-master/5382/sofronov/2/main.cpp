#include "Shapes.h"


int main() {
    Point point1(1.0,1.0);
    Point point2(2.0,2.0);
    Point point3(10,-10);
    Point point4(15,-15);
    Arc tmp_arc (point1, point2, 90, red);
    tmp_arc.zoom(10);


    //tmp_arc.move(point3);
    std::cout << tmp_arc;


    Ellipse tmp_ellipse (point3, point4, blue);
    //tmp_ellipse.zoom(10);
    std::cout << tmp_ellipse;

    std::cout << tmp_arc.doinsert(tmp_ellipse);

    return 0;
}


