#pragma once

#include "objects/units/unit.h"
#include "memory"
#include "field.h"
#include <stdio.h>
#include "field.h"

class FieldIterator
{
public:
    FieldIterator(const Field& field);

    bool hasNext() const;
    void first();
    friend const FieldIterator& operator++(FieldIterator& it);
    friend const FieldIterator operator++(FieldIterator& it, int);
    //Cell& operator*() const;

private:
    int i;
    int j;
    int width;
    int height;
    const Field& field;
};

