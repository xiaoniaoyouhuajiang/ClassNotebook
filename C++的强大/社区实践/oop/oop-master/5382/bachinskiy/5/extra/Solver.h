//
// Created by Максим Бачинский on 16.05.17.
//

#ifndef INC_5_SOLVER_H
#define INC_5_SOLVER_H


#include "../figures/Shape.h"
#include "../pointer/shared_ptr.h"
#include "../list/list.h"

using namespace stepik;

class Solver {
public:
    // TODO: find first figure
    shared_ptr<Shape> findFirstElement(const list<shared_ptr<Shape>>& listOfShapes,
                                       shared_ptr<Shape>& shape1, shared_ptr<Shape>& shape2);
    // TODO: replace all elements by another element
    void replaceAllElements(list<shared_ptr<Shape>>& listOfShapes,
                            shared_ptr<Shape>& shape1, shared_ptr<Shape>& shape2, shared_ptr<Shape>& replacingElements);
};


#endif //INC_5_SOLVER_H
