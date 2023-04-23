#include <iostream>

#include "lab5.h"

using namespace stepik;

int main(/*int argc, char *argv[]*/)
{
    Shape *sq1 = new Quadrate(0, 0, 10, 0, 10, 10, 0, 10, Color());
    Shape *sq2 = new Quadrate(2, 2, 2, 7, 7, 7, 7, 2, Color());

    Shape *is1 = new IsoscelesTriangle(-3, 0, -2, 2, -1, 0, Color());
    Shape *is2 = new IsoscelesTriangle(0, 0, 3, 2, 6, 0, Color());

    Shape *rt1 = new RightTriangle(-2, 0, -2, 5, 3, 0, Color());
    Shape *rt2 = new RightTriangle(-1, 1, -1, 2, 0, 1, Color());


    list< shared_ptr<Shape> > l;
    l.push_back(shared_ptr<Shape>(sq1));
    l.push_back(shared_ptr<Shape>(sq2));
    l.push_back(shared_ptr<Shape>(is1));
    l.push_back(shared_ptr<Shape>(is2));
    l.push_back(shared_ptr<Shape>(rt1));
    l.push_back(shared_ptr<Shape>(rt2));

    std::cout<<"Nonmodify Algorithm"<<std::endl;
    list_iterator< shared_ptr<Shape> > res = std::find_if(l.begin(), l.end(), isInside);
    (res)->get()->put(std::cout);

    std::cout<<"Modify Algorithm"<<std::endl;
    std::partition(l.begin(), l.end(), isInside);

    for(auto it : l)
    {
        it.get()->put(std::cout);
    }

    delete sq1;
    delete sq2;
    delete is1;
    delete is2;
    delete rt1;
    delete rt2;

    return 0;
}
