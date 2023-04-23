#include "iterator.h"

Iterator::Iterator(Field *field): field(field), x(-1), y(0)
{
    cell = field->cell[0][0];
}

bool Iterator::operator!= (const Iterator& iter) {
    if(x != iter.x || y != iter.y)
        return false;
    return true;
}

bool Iterator::goNext()
{
    if(x==field->x-1 && y==field->y-1)
        return false;

    if(x==field->x-1) {
        x = 0;
        y++;
    }
    else {
        x++;
    }

    cell = field->cell[y][x];
    return true;
}