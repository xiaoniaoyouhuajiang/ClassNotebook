//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_REFRESH_H
#define OOP_NEW_REFRESH_H


#include "../INeutralStrategy.h"

/* Refresh -- конкретная стратегия поведения для
 * нейтрального объекта Curse.
 */

class Refresh : public INeutralStrategy
{
    void impact(Object* unit) override;
};


#endif //OOP_NEW_REFRESH_H
