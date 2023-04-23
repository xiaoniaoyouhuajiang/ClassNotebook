//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_GAMEFIELDITERATOR_H
#define UNTITLED13_GAMEFIELDITERATOR_H

#include <iterator>
#include "Point.h"
#include "Units/Unit.h"

class GameFieldIterator: public std::iterator<std::input_iterator_tag, Unit*>{

    friend class GameField;

private:

    Point p;
    Unit *** field;
    const int fieldHeight;
    const int fieldWidth;

    GameFieldIterator(const Point p, Unit *** field, const int fieldHeight, const int fieldWidth):
    p(p),
    field(field),
    fieldWidth(fieldWidth),
    fieldHeight(fieldHeight){};

public:

    GameFieldIterator(const GameFieldIterator &it):
    p(it.p),
    field(it.field),
    fieldWidth(it.fieldWidth),
    fieldHeight(it.fieldHeight){};

    bool operator!=(const GameFieldIterator &other) { return p != other.p; };
    bool operator==(const GameFieldIterator &other) { return p == other.p; };
    typename GameFieldIterator::reference operator*() { return  field[p.y][p.x]; };

    GameFieldIterator&  operator++() {

        Point next = p;
        next.x++;

        if (next.x < fieldWidth) {
            p = next;
            return *this;
        } else{

            next.x = 0;
            next.y++;

            p = next;
            return *this;
        }

    };


};

#endif //UNTITLED13_GAMEFIELDITERATOR_H
