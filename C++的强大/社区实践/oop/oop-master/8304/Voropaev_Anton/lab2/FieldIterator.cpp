
#include "FieldIterator.h"


Iterator::Iterator( Field& field) : gameField(field) {
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


const bool operator==(Iterator& left, Iterator& right) {
    return (right.i == left.i) && (left.j == right.j);
}


const bool operator!=(Iterator& left, Iterator& right) {
    return !(left == right);
}


Iterator& Iterator::operator=(const Iterator& it) {
    if(this != &it) {
        this->gameField = it.gameField;
        this->height = it.height;
        this->width = it.width;
        this->i = it.i;
        this->j = it.j;
    }
    return *this;
}


const bool operator<(Iterator& left, Iterator& right) {
    if (left.i > left.j)
        return false;
    else if (left.i < left.j)
        return true;
    else
        return left.j < right.j;
}


const bool operator<=(Iterator& left, Iterator& right) {
    return (left < right) || (left == right);
}


const bool operator>(Iterator& left, Iterator& right) {
    return (right < left);
}


const bool operator>=(Iterator& left, Iterator& right) {
    return (right < left) || (right == left);
}


cell Iterator::operator*() const {
    return ((gameField.getHead()[i][j]));
}

