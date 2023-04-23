//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_HEALTHDOWN_H
#define OOP_NEW_HEALTHDOWN_H


#include "../INeutralStrategy.h"

/* HealthDown -- конкретная стратегия поведения для
 * нейтрального объекта Trap.
 */

class HealthDown : public INeutralStrategy
{
    void impact(Object* unit) override;
};


#endif //OOP_NEW_HEALTHDOWN_H
