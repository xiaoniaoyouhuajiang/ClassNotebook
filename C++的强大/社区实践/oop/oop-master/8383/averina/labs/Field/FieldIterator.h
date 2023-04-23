#ifndef OOP_FIELDITERATOR_H
#define OOP_FIELDITERATOR_H

#include "Field.h"
class Field;

//  FieldIterator -- класс итератора игрового поля.

class FieldIterator
{
public:
    explicit FieldIterator(Field& field);
    ~FieldIterator() = default;

    void begin();
    void end();

    friend const FieldIterator& operator++(FieldIterator& it);
    friend const FieldIterator& operator--(FieldIterator& it);

private:
    int x, y;
    int height;
    int width;

    Field& field_;
};

#endif //OOP_FIELDITERATOR_H
