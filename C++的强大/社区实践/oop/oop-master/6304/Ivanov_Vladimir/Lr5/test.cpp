#include "vector.hpp"
#include "shared.hpp"
#include "figure.hpp"
#include "algs.hpp"
#include <cassert>

using namespace last;

void createRects(vector<shared_ptr<Shape>>& mass, int size){
    for(int i=0;i<size;i++){
        mass[i]=shared_ptr<Shape>(new Rectangle(3,3,5+i,5+i));
    }
}

void createElls(vector<shared_ptr<Shape>>& mass, int size){
    for(int i=0;i<size;i++){
        mass[i]=shared_ptr<Shape>(new Ellipse(3,3,1+i,1+i));
    }
}

void createPents(vector<shared_ptr<Shape>>& mass, int size){
    for(int i=0;i<size;i++){
        mass[i]=shared_ptr<Shape>(new Pentagon(2,0,3,1,1,1,1,i+2,3,i+2));
    }
}

void TestNoMod(){
    vector<shared_ptr<Shape>> mass(5);
    createRects(mass, mass.size());
    assert(allsquareless(mass,20)==true); //min square=25, max square=81
    assert(allsquareless(mass,40)==false);

    createElls(mass, mass.size());
    assert(allsquareless(mass,3)==true); //min square=3.14, max square=78.5
    assert(allsquareless(mass,4)==false);

    createPents(mass, mass.size());
    assert(allsquareless(mass,2)==true); //min square=3, max square=11
    assert(allsquareless(mass,4)==false);
}

void TestMod(){
    vector<shared_ptr<Shape>> mass(5);

    //Checking for 1 bad element
    createRects(mass, mass.size());
    copyBad(mass,80); //min square=25, max square=81
    assert(mass.size()==6);
    //Checking for all bad elements
    createElls(mass, mass.size()); //curr size=6
    copyBad(mass,3); //min square=3.14, max square=113.04
    assert(mass.size()==12);
    //Checking for all good elements
    createPents(mass, mass.size()); //curr size=12
    copyBad(mass,26); //min square=3, max square=25
    assert(mass.size()==12);
}

int main(){
    TestNoMod();
    TestMod();
    std::cout<<"Всё хорошо\n";
    return 0;
}