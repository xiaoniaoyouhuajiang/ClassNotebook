//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_MANAUP_H
#define OOP_NEW_MANAUP_H


#include "../INeutralStrategy.h"

/* ManaUp -- конкретная стратегия поведения для
 * нейтрального объекта Potion.
 */

class ManaUp : public INeutralStrategy
{
    void impact(Object* unit) override;
};


#endif //OOP_NEW_MANAUP_H
