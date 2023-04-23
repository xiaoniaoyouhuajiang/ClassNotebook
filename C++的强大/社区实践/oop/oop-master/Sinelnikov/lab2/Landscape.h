//
// Created by max on 04.03.20.
//

#ifndef OOP_LANDSCAPE_H
#define OOP_LANDSCAPE_H

#include <string.h>
#include "Unit.h"
#include "Object.h"
#include <map>

using std::map;

class Landscape : public Object  {
public:
    Landscape(int x,int y,int id) : Object(x,y,id)
    {

    }
    virtual ~Landscape() = 0;
};

#endif //OOP_LANDSCAPE_H
