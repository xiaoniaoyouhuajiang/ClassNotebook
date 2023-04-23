//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_BLOCKENTITY_H
#define OOPROJECT_BLOCKENTITY_H

#include "Entity.h"

class BlockEntity :public Entity{
public:
    BlockEntity(int x, int y, Devotion devotion, int health);

private:
    void react(std::shared_ptr<GameObject> sbj) override;

    void restep(std::shared_ptr<GameObject> sbj) override;

    CommonClass getObjectClass() override;

};


#endif //OOPROJECT_BLOCKENTITY_H
