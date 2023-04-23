
#ifndef OOP_HELTHDOWN_H
#define OOP_HELTHDOWN_H


#include "INeutralStrategy.h"

/* HealthDown -- конкретная стратегия поведения для
 * нейтрального объекта Trap.
 */

class HealthDown : public INeutralStrategy
{
    void impact(Object* unit) override;
};

#endif //OOP_HELTHDOWN_H
