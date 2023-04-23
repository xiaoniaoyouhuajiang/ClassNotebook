//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_TRAP_H
#define OOP_NEW_TRAP_H


#include "../INeutral.h"
#include "../../../Strategies/TrapStrategy/HealthDown.h"

/* Trap -- класс нейтрального объекта - ловушки.
 * Связан с интерфейсом стратегий нейтральных объектов.*/

class Trap : public INeutral
{
public:
    Trap();
    void getEffect(Object *unit) override;
    void operator>>(Object* unit) override;
};


#endif //OOP_NEW_TRAP_H
