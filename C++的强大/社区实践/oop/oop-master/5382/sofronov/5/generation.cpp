#include "Shapes.h"
#include "List.h"
#include "shared_ptr.h"

const int SHAPES_NUM = 1000;

list<shared_ptr<Shape>> generation () {

    list<shared_ptr<Shape>> my_list;

    for (size_t i = 0; i < SHAPES_NUM; i++) {
        switch(rand()%3) {
            case 0:
                my_list.push_back(shared_ptr<Shape>(new Arc));
                break;
            case 1:
                my_list.push_back(shared_ptr<Shape>(new Circle));
                break;
            case 2:
                my_list.push_back(shared_ptr<Shape>(new Ellipse));
                break;


            default:
                break;
        }
    }
    return my_list;
}

