//
// Created by Максим Бачинский on 16.05.17.
//

#include "Solver.h"

shared_ptr<Shape>
Solver::findFirstElement(const list<shared_ptr<Shape>>& listOfShapes, shared_ptr<Shape>& shape1, shared_ptr<Shape>& shape2) {
    list_iterator<shared_ptr<Shape>> it = listOfShapes.begin();
    for (; it != listOfShapes.end(); it++) {
        Shape& s = *(*it);
        if (s.isUnionOf(*shape1, *shape2)) {
            return *it;
        }
    }
    return shared_ptr<Shape>();
}

void
Solver::replaceAllElements(list<shared_ptr<Shape>>& listOfShapes, shared_ptr<Shape>& shape1, shared_ptr<Shape>& shape2,
                           shared_ptr<Shape>& replacingElements) {
    list_iterator<shared_ptr<Shape>> it = listOfShapes.begin();
    for (int i = 0; i < listOfShapes.size(); ++i) {
        Shape& s = *(*it);
        if (s.isUnionOf(*shape1, *shape2)) {
            listOfShapes.insert(it, replacingElements);
            it = listOfShapes.erase(it);
        } else {
            it++;
        }


    }
}
