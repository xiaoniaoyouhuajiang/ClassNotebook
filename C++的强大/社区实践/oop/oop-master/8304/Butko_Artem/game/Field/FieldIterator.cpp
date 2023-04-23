#include "FieldIterator.h"

FieldIterator::FieldIterator(const GameField &field) : field_(field)
{
    this->height_ = field.height_;
    this->width_ = field.width_;
    this->x_ = 0;
    this->y_ = 0;
}

void FieldIterator::begin()
{
    x_ = 0;
    y_ = 0;
}

void FieldIterator::end()
{
    x_ = height_ - 1;
    y_ = width_ - 1;
}

const FieldIterator &operator++(FieldIterator &it)
{
    if (it.y_ + 1 < it.width_)
        ++it.y_;
    else if (it.x_ != it.height_)
    {
        ++it.x_;
        it.y_ = 0;
    }
    return it;
}

const FieldIterator &operator--(FieldIterator &it) {
    if (it.y_ > 0)
        --it.y_;
    else if (it.x_ >= 0)
    {
        --it.x_;
        it.y_ = 0;
    }
    else
    {
        it.x_ = 0;
        it.y_ = 0;
    }
    return it;
}


