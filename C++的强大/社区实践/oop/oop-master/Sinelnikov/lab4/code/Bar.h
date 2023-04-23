//
// Created by max on 13.03.20.
//

#ifndef OOP_BAR_H
#define OOP_BAR_H

#include "NeutralObject.h"

class Bar : public NeutralObject {
public:
    Bar(int x,int y,int id) : NeutralObject(x,y,id)
    {

    }
    ~Bar()
    {

    }
    void communication(Unit* unit);
};


#endif //OOP_BAR_H
