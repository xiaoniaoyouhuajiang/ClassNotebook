//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_INEUTRAL_H
#define OOP_NEW_INEUTRAL_H


#include "../Object.h"
#include "../../Strategies/INeutralStrategy.h"

/*
 * INeutral -- интерфейс нейтрального объекта.
 */

class INeutral : public Object
{
public:
    virtual void getEffect(Object* unit) = 0;
    virtual void operator>>(Object* unit) = 0;
    INeutralStrategy* action;
};


#endif //OOP_NEW_INEUTRAL_H
