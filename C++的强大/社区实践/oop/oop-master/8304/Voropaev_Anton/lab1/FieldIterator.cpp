
#include "FieldIterator.h"
#include "Unit.h"
#include "Field.h"


Iterator::Iterator(const Field& field) : gameField(field) {
    this->i = 0;
    this->j = 0;
    this->width = field.getSize().width;
    this->height = field.getSize().height;
}


bool Iterator::hasNext() const
{
    return i < gameField.getSize().height && j < gameField.getSize().width;

}


void Iterator::first()
{
    j = 0;
    i = 0;
}


const Iterator& operator++(Iterator& it)
{
    if (it.j + 1 < it.width) {
        ++it.j;
    }
    else {
        ++it.i;
        it.j = 0;
    }

    return it;
}

const Iterator& operator--(Iterator& it)
{
    if (it.j - 1 >= 0) {
        --it.j;
    }
    else {
        --it.i;
        it.j = it.width - 1;
    }

    return it;
}


Unit* Iterator::operator*() const
{
    return ((gameField.GetHead())[i * this->width + j]);
}

