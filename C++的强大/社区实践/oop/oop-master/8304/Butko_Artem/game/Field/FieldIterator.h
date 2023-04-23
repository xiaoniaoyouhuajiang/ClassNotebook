#ifndef NEW_LR1_FIELDITERATOR_H
#define NEW_LR1_FIELDITERATOR_H

#include "GameField.h"

class GameField;

class FieldIterator
{
    FieldIterator(const GameField& field);
    ~FieldIterator() = default;

    void begin();
    void end();
    friend const FieldIterator& operator++(FieldIterator& it);
    friend const FieldIterator& operator--(FieldIterator& it);
    int x_;
    int y_;
    int height_;
    int width_;
    const GameField &field_;
};


#endif //NEW_LR1_FIELDITERATOR_H
