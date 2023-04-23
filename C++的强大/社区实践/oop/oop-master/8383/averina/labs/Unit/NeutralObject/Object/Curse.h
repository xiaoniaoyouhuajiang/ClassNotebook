
#ifndef OOP_CURSE_H
#define OOP_CURSE_H

#include "INeutral.h"



/* Curse - класс нейтрального объекта - проклятия.
 * Связан с интерфейсом стратегий нейтральных объектов.*/

class Curse : public INeutral
{
public:
    Curse();
    void getEffect(Object* unit) override;
    void operator>>(Object* unit) override;
};



#endif //OOP_CURSE_H
