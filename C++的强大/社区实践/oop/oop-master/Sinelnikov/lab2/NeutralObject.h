//
// Created by max on 06.03.20.
//

#ifndef OOP_NEUTRALOBJECT_H
#define OOP_NEUTRALOBJECT_H

#include "Object.h"
#include "Unit.h"

class NeutralObject : public  Object{
public:
    NeutralObject(int x,int y,int id) : Object(x,y,id)
    {

    }
    ~NeutralObject()
    {

    }
    Unit* operator+(Unit* unit);
    virtual void communication(Unit* unit) = 0;
};

#endif //OOP_NEUTRALOBJECT_H
