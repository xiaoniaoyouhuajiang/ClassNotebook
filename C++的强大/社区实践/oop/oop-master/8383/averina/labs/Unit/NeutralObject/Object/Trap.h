#ifndef OOP_TRAP_H
#define OOP_TRAP_H


#include "../../Object/Object.h"
#include "INeutral.h"

/* Trap -- класс нейтрального объекта - ловушки.
 * Связан с интерфейсом стратегий нейтральных объектов.*/

class Trap : public INeutral
{
public:
    Trap();
    void getEffect(Object *unit) override;
    void operator>>(Object* unit) override;
};


#endif //OOP_TRAP_H
