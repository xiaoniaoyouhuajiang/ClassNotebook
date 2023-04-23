//
// Created by max on 06.03.20.
//

#ifndef OOP_PUBLICHOUSE_H
#define OOP_PUBLICHOUSE_H

#include "NeutralObject.h"

class PublicHouse : public NeutralObject{
public:
    PublicHouse(int x,int y,int id) : NeutralObject(x,y,id)
    {

    }
    ~PublicHouse()
    {

    }
    void communication(Unit* unit);
};


#endif //OOP_PUBLICHOUSE_H
