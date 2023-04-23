#ifndef OOP_POTION_H
#define OOP_POTION_H

#include "INeutral.h"

/* Potion -- зелье -- класс нейтрального объекта
 * Связан с интерфейсом стратегий нейтральных объектов.*/

class Potion : public INeutral
{
public:
    Potion();
    void getEffect(Object* unit) override;
    void operator>>(Object* unit) override;
};



#endif //OOP_POTION_H
