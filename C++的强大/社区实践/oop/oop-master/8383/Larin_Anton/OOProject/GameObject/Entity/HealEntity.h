//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_HEALENTITY_H
#define OOPROJECT_HEALENTITY_H

#include "Entity.h"

class HealEntity :public Entity{
public:
    HealEntity(int x, int y, Devotion devotion, int healAmount);

private:
    void react(std::shared_ptr<GameObject> sbj) override;

    void restep(std::shared_ptr<GameObject> sbj) override;

    CommonClass getObjectClass() override;

private:
    int healAmount;
};


#endif //OOPROJECT_HEALENTITY_H
