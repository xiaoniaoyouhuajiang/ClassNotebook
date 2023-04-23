
#ifndef OOP_MANAUP_H
#define OOP_MANAUP_H


#include "INeutralStrategy.h"

/* ManaUp -- конкретная стратегия поведения для
 * нейтрального объекта Potion.
 */

class ManaUp : public INeutralStrategy
{
    void impact(Object* unit) override;
};


#endif //OOP_MANAUP_H
