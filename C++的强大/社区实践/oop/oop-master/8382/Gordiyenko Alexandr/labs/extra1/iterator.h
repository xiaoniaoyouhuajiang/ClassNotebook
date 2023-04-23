#ifndef LABS_ITERATOR_H
#define LABS_ITERATOR_H

#include "../Field.h"
#include "../Units/Unit.h"
class Iterator {
    Field* field;
public:
    int x, y;
    bool isfind = false;
    Cell* cell;
    Iterator(Field* field);

    Cell*& operator*() {
        return cell;
    }

    bool operator!= (const Iterator& iter);
    bool goNext();
};

#endif //LABS_ITERATOR_H
