//
// Created by max on 04.03.20.
//

#ifndef OOP_FOREST_H
#define OOP_FOREST_H

#include "Landscape.h"

class Forest : public Landscape {
public:
    Forest(int x,int y,int id) : Landscape(x,y,id)
    {

    }
    ~Forest()
    {

    }
};


#endif //OOP_FOREST_H
