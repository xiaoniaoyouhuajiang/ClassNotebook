#ifndef battlefielditerator_hpp
#define battlefielditerator_hpp

#include "BattleField.hpp"

#include <stdio.h>

class BattleFieldIterator
{
public:
    BattleFieldIterator(const BattleField& battleField);

    bool hasNext() const;
    void first();
    friend const BattleFieldIterator& operator++(BattleFieldIterator& it);
    friend const BattleFieldIterator operator++(BattleFieldIterator& it, int);
    FieldCell& operator*() const;

private:
    size_t i;
    size_t j;
    size_t width;
    size_t height;
    const BattleField& battleField;
};

#endif /* battlefielditerator_hpp */
