#ifndef ITERATOR_H
#define ITERATOR_H

#include "gamefield.h"
#include "Units/unit.h"

class Iterator
{
    const GameField* field;
    Unit* cur;
    int x, y;

public:
    Iterator(GameField* );

    bool hasNext();
    Unit*& operator++ (int);
    bool operator!= (const Iterator&);
    Unit*& operator* ();

private:
    int isFirstIter;
};

#endif // ITERATOR_H
