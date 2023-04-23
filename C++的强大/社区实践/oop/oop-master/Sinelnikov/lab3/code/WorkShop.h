//
// Created by max on 13.03.20.
//

#ifndef OOP_WORKSHOP_H
#define OOP_WORKSHOP_H

#include "NeutralObject.h"
#include "Unit.h"

class WorkShop : public NeutralObject{
public:
    WorkShop(int x,int y,int id) : NeutralObject(x,y,id)
    {
    }
    ~WorkShop()
    {

    }
    virtual void communication(Unit* unit);
};


#endif //OOP_WORKSHOP_H
