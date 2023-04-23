//
// Created by anton on 5/25/20.
//

#ifndef OOPROJECT_ABSTRACTFACTORY_H
#define OOPROJECT_ABSTRACTFACTORY_H

#include <memory>

#include "../GameObject/GameObject.h"

class AbstractFactory {
public:
    virtual std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion)=0;
};


#endif //OOPROJECT_ABSTRACTFACTORY_H
