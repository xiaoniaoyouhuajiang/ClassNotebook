#include <iostream>
#include "Vector.cpp"
#include "shape.h"
using namespace std;

void turnVector(Vector<Shape*> VecRec){
     for(size_t i=0;i<VecRec.size();i++){
     cout<<"Before turn:\n\n";
     cout<<*VecRec[i]<<endl;
     VecRec[i]->turn(180);
     cout<<"\nAfter turn:\n\n";
     cout<<*VecRec[i]<<endl;
     }
}



int main(){
    Vector<Shape*> VecRec;
    Rectangle* rect = new Rectangle(point(0, 0), 2, 2);
    Parallelogram* Paral = new Parallelogram(point(-3, 5), 3, 5, 30);
    Regular_Hexagon* Hexagon = new Regular_Hexagon(point(-5 ,4),3);
    VecRec.push_back(rect);
    VecRec.push_back(Paral);
    VecRec.push_back(Hexagon);
    rect = new Rectangle(point(5 ,10), 5, 4);
    Hexagon = new Regular_Hexagon(point(4, 4), 1);
    VecRec.push_back(Hexagon);
    VecRec.push_back(rect);
    turnVector(VecRec);
    return 0;
}
