//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_POTION_H
#define OOP_NEW_POTION_H


#include "../INeutral.h"
#include "../../../Strategies/PotionStrategy/ManaUp.h"

/* Potion -- класс нейтрального объекта - проклятия.
 * Связан с интерфейсом стратегий нейтральных объектов.*/

class Potion : public INeutral
{
public:
    Potion();
    void getEffect(Object* unit) override;
    void operator>>(Object* unit) override;
};


#endif //OOP_NEW_POTION_H
