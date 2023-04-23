//
// Created by Artem Butko on 14/05/2020.
//

#include "FieldIterator.h"

FieldIterator::FieldIterator(Field &field) : field_(field)
{
    this->height = field.height;
    this->width = field.width;
    this->x = 0;
    this->y = 0;
}

void FieldIterator::begin()
{
    x = 0;
    y = 0;
}

void FieldIterator::end()
{
    x = width - 1;
    y = height - 1;
}

const FieldIterator& operator++(FieldIterator &it)
{
    if (it.x + 1 < it.width)
        ++it.x;
    else if (it.y != it.height)
    {
        ++it.y;
        it.x = 0;
    }
    return it;
}

const FieldIterator& operator--(FieldIterator &it)
{
    if (it.x > 0)
        --it.x;
    else if (it.x == 0 && it.y >=0)
    {
        it.x = it.width - 1;
        it.y --;
    }
    else
    {
        it.x = 0;
        it.y = 0;
    }
    return it;
}



