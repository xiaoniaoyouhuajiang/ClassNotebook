
#ifndef OOP_REFRESH_H
#define OOP_REFRESH_H

#include "Strategy/INeutralStrategy.h"

/* Refresh -- конкретная стратегия поведения для
 * нейтрального объекта Curse.
 */

class Refresh : public INeutralStrategy
{
    void impact(Object* unit) override;
};



#endif //OOP_REFRESH_H
