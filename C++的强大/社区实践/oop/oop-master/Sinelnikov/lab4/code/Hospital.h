//
// Created by max on 06.03.20.
//

#ifndef OOP_HOSPITAL_H
#define OOP_HOSPITAL_H

#include "NeutralObject.h"
#include "Unit.h"

class Hospital : public NeutralObject {
public:
    Hospital(int x,int y,int id) : NeutralObject(x,y,id)
    {

    }
    ~Hospital()
    {

    }
    void communication(Unit* unit);
};

#endif //OOP_HOSPITAL_H
