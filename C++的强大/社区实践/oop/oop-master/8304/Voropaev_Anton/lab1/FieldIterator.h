
#ifndef OOP_FIELDITERATOR_H
#define OOP_FIELDITERATOR_H

#include <cstdio>


class Field;
class Unit;

class Iterator
{
public:
    explicit Iterator(const Field& field);

    bool hasNext() const;
    void first();
    friend const Iterator& operator--(Iterator& it);
    friend const Iterator& operator++(Iterator& it);
    Unit* operator*() const;


private:
    size_t i;
    size_t j;
    size_t width;
    size_t height;
    const Field& gameField;
};




#endif //OOP_FIELDITERATOR_H
