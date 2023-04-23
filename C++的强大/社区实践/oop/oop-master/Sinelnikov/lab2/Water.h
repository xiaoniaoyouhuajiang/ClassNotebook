//
// Created by max on 04.03.20.
//

#ifndef OOP_WATER_H
#define OOP_WATER_H

#include "Landscape.h"


class Water : public Landscape {
public:
    Water(int x,int y,int id) : Landscape(x,y,id)
    {

    }
    ~Water()
    {

    }
};


#endif //OOP_WATER_H
