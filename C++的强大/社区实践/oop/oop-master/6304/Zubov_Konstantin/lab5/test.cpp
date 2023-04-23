#include "vector.hpp"
#include "shared.hpp"
#include "figure.hpp"
#include "algs.hpp"
#include <cassert>

using namespace last;

void createArcs(vector<shared_ptr<Shape>>& mass, int size){
    for(int i=0;i<size;i++){
        mass[i]=shared_ptr<Shape>(new Arc(1, 1, 0.5+i, 30,60));
    }
}

void createElls(vector<shared_ptr<Shape>>& mass, int size){
    for(int i=0;i<size;i++){
        mass[i]=shared_ptr<Shape>(new Ellipse(2,2,2+i,1+i));
    }
}

void createCircs(vector<shared_ptr<Shape>>& mass, int size){
    for(int i=0;i<size;i++){
        mass[i]=shared_ptr<Shape>(new Circle(0,0,1+i));
    }
}

void TestNoMod(){
    vector<shared_ptr<Shape>> a(5);
    vector<shared_ptr<Shape>> b(5);
    vector<shared_ptr<Shape>> c(5);
    createArcs(a, a.size());
    createElls(b, b.size());
    createCircs(c, c.size());
    assert(search(a,b)==true);
    assert(search(b,c)==true);
    assert(search(c,c)==false);
}

void TestMod(){

    vector<shared_ptr<Shape>> a(5);
    vector<shared_ptr<Shape>> b(5);
    vector<shared_ptr<Shape>> c(5);

    createArcs(a, a.size());
    createElls(b, b.size());
    createCircs(c, c.size());
    vector<shared_ptr<Shape>> f=intersection(a,b);
    vector<shared_ptr<Shape>> d=intersection(a,a);
    vector<shared_ptr<Shape>> e=intersection(a,c);
    assert(f.size()==0);
    assert(d.size()==5);
    assert(e.size()==0);


}

int main(){
    TestNoMod();
    TestMod();
    std::cout<<"Всё хорошо\n";
    return 0;
}
