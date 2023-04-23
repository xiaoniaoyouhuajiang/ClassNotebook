
#ifndef OOP_DAMN_H
#define OOP_DAMN_H

#include "INeutralStrategy.h"

/* Damn -- конкретная стратегия поведения для
 * нейтрального объекта Curse.
 */

class Damn : public INeutralStrategy
{
    void impact(Object* unit) override;
};


#endif //OOP_DAMN_H
