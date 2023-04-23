#include <iostream>
#include <cstdlib>
#include <cmath>

#include "point.h"
#include "shape.hpp"
#include "circle.hpp"
#include "pentagon.hpp"
#include "regular_pentagon.hpp"

#include "shared_ptr.hpp"
#include "vector.hpp"

#include "alg.hpp"

#define N 1000

using namespace std;

int main(){
    stepik::vector<stepik::shared_ptr<Shape>> vect(N);
    srand(time(0));
    short int choice = 0;
    for (int i = 0; i < N; i++){
        choice = rand() % 3;
        Shape* shp;
        switch (choice){
            case 0: shp = new Circle(Point().Rand(0, 1000), rand()%100); break;
            case 1: shp = new RegularPentagon(Point().Rand(0, 1000), rand()%100); break;
            case 2: shp = new Pentagon(0, 1000); break;
        }
        stepik::shared_ptr<Shape> ptr(shp);
        vect[i] = ptr;
    }
    Shape* toReplace = new Circle(Point(500, 500), 500);
    stepik::shared_ptr<Shape> toReplacePtr(toReplace);
    size_t max = getMaxSq(vect);
    printMaxSq(vect);
    double sq = vect[max]->square();
    replaceSq(vect, toReplacePtr, sq - 1);
    cout << "---" << endl;
    printMaxSq(vect);
}