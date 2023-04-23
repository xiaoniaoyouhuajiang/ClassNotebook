//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_DAMN_H
#define OOP_NEW_DAMN_H


#include "../INeutralStrategy.h"

/* Damn -- конкретная стратегия поведения для
 * нейтрального объекта Curse.
 */

class Damn : public INeutralStrategy
{
    void impact(Object* unit) override;
};


#endif //OOP_NEW_DAMN_H
