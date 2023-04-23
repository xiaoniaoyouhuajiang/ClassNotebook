//
// Created by anton on 5/27/20.
//

#include "BaseFactory.h"

#include "../../GameObject/Base/Base.h"

//BaseFactory::BaseFactory(int lim) : lim(lim) {}

std::shared_ptr<Base> BaseFactory::createBase(int x, int y, Devotion devotion) {
    //new Base(x, y, devotion, CommonClass::Base, baseHealth, EntityType::Base, lim);
    auto rPtr = std::make_shared<Base>(x, y, devotion, CommonClass::Base, baseHealth, EntityType::Base, lim);
    //return std::static_pointer_cast<GameObject>(rPtr);
    return rPtr;
}

BaseFactory::BaseFactory(int lim, int baseHealth, int baseArmour, int baseDmgmul) : lim(lim), baseHealth(baseHealth),
                                                                                    baseArmour(baseArmour),
                                                                                    baseDmgmul(baseDmgmul) {}

std::shared_ptr<GameObject> BaseFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<Base>(x, y, devotion, CommonClass::Base, baseHealth, EntityType::Base, lim);
    return std::static_pointer_cast<GameObject>(rPtr);
}
