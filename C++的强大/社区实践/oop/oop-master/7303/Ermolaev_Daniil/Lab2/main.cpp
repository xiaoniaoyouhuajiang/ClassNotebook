#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <math.h>

#include "shape.h"
#include "parallelogram.h"
#include "rhombus.h"
#include "square.h"

using namespace std;

/*
TO DO:
id -> static (*)
yuml
separate files (*)
examples of work
equality thought the area (*)
<< w\o freind?? (*)
*/

int main() {
    Shape * shp = new Square(5,{0,0});
    Shape * shp2 = new Rhombus(8,5,{0,0});

    cout << *shp << endl << *shp2 << endl;

    shp->scale(2);
    //shp2->rotate(90);

    cout << *shp << endl << *shp2 << endl;
    cout << shp->getArea() << ' ' << ((*shp)==(*shp2)) << ' ' << shp2->getArea() << endl;

    return 0;
}
