//
// Created by anton on 5/28/20.
//

#include "BlockFactory.h"

#include "../../GameObject/Entity/BlockEntity.h"



std::shared_ptr<GameObject> BlockFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<BlockEntity>(x,y,devotion,blockHealth);
    return std::static_pointer_cast<GameObject>(rPtr);
}

BlockFactory::BlockFactory(int blockHealth) : blockHealth(blockHealth) {}
