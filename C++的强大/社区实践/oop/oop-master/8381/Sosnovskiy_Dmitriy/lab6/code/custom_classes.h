#pragma once
#include "enums.h"

class CoordsInfo{
public:
    unsigned int row;
    unsigned int column;
    CoordsInfo(unsigned int row, unsigned int column) :
        row(row), column(column) { }
};


class NeutralObjectInfo{
public:
    NeutralObjectType type;
    CoordsInfo* coordinate;
    NeutralObjectInfo(NeutralObjectType type, CoordsInfo* coordinate){
        this->type = type;
        this->coordinate = coordinate;
    }
};
