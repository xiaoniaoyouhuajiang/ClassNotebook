


#include "../../Object/Object.h"
#include "../Strategy/INeutralStrategy.h"

/*
 * INeutral -- интерфейс нейтрального объекта.
 */

class INeutral : public Object
{
public:
    virtual void getEffect(Object* unit) = 0;
    virtual void operator>>(Object* unit) = 0;
    INeutralStrategy* action;
};