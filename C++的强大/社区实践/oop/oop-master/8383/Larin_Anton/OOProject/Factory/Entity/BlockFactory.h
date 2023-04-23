//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_BLOCKFACTORY_H
#define OOPROJECT_BLOCKFACTORY_H

#include "AbstractEntityFactory.h"

class BlockFactory:public AbstractEntityFactory {
private:
    int blockHealth;

public:

    BlockFactory(int blockHealth);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

};


#endif //OOPROJECT_BLOCKFACTORY_H
