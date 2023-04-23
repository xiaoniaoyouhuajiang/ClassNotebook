//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_INEUTRALSTRATEGY_H
#define OOP_NEW_INEUTRALSTRATEGY_H


#include "../Objects/Units/IUnit.h"

/* INeutralStrategy -- интерфейс стратегии нейтрального объекта.
 */

class INeutralStrategy
{
public:
    virtual void impact(Object* unit) = 0;
};


#endif //OOP_NEW_INEUTRALSTRATEGY_H
