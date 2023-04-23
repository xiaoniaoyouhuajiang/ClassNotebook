
#ifndef OOP_INEUTRALSTRATEGY_H
#define OOP_INEUTRALSTRATEGY_H

#include "../../Object/Object.h"

/* INeutralStrategy -- интерфейс стратегии нейтрального объекта.*/

class INeutralStrategy{

public:
    virtual void impact(Object* unit) = 0;
};


#endif //OOP_INEUTRALSTRATEGY_H
