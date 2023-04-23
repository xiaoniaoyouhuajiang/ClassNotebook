//
// Created by max on 04.03.20.
//

#ifndef OOP_PLAIN_H
#define OOP_PLAIN_H

#include "Landscape.h"

class Plain : public Landscape {
public:
    Plain(int x,int y,int id) : Landscape(x,y,id)
    {

    }
    ~Plain()
    {

    }
};


#endif //OOP_PLAIN_H
