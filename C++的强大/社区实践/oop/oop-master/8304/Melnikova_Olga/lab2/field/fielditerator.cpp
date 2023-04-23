#include "fielditerator.h"



FieldIterator::FieldIterator(const Field& field) : field(field)
{
    this->i = 0;
    this->j = 0;
    this->width = field.W;
    this->height = field.H;
}


bool FieldIterator::hasNext() const
{
    if (i < field.H && j < field.W) {
        return true;
    }

    return false;
}


void FieldIterator::first()
{
    j = 0;
    i = 0;
}


const FieldIterator& operator++(FieldIterator& it)
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


const FieldIterator operator++(FieldIterator& it, int)
{
    FieldIterator tmp(it);
    ++it;
    return tmp;
}


/*Cell& FieldIterator::operator*() const
{

    return field._cells[i][j];
}*/
