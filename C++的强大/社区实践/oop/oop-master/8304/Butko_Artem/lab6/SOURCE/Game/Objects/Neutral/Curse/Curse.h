//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_CURSE_H
#define OOP_NEW_CURSE_H


#include "../INeutral.h"
#include "../../../Strategies/CurseStrategy/Damn.h"

/* Curse -- класс нейтрального объекта - проклятия.
 * Связан с интерфейсом стратегий нейтральных объектов.*/

class Curse : public INeutral
{
public:
    Curse();
    void getEffect(Object* unit) override;
    void operator>>(Object* unit) override;
};


#endif //OOP_NEW_CURSE_H
