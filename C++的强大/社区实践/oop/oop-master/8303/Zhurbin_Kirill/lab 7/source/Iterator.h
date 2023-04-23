#ifndef OOP1_ITERATOR_H
#define OOP1_ITERATOR_H

#include "Unit.h"
#include "Field.h"

class Iterator{
    Field& field;

private:
    int x, y;
    bool isFind = false;
public:

    Iterator(Field &field);
    bool operator!= (const Iterator& iter);
    Unit*& operator* ();
    bool hasNext();
};

#endif //OOP1_ITERATOR_H
