//
// Created by max on 04.03.20.
//

#ifndef OOP_MOUNTAIN_H
#define OOP_MOUNTAIN_H

#include "Landscape.h"

class Mountain : public Landscape{
public:
    Mountain(int x,int y,int id) : Landscape(x,y,id)
    {

    }
    ~Mountain()
    {

    }
};


#endif //OOP_MOUNTAIN_H
