//
// Created by anton on 3/17/20.
//

#include "FieldCellProxy.h"

#include "Mediator.h"

FieldCellProxy::FieldCellProxy(Mediator *mediator1, int x1, int y1) {
    mediator = mediator1;
    x = x1;
    y = y1;
}

LandscapeProxy FieldCellProxy::getLandscape() const {
    return LandscapeProxy(mediator, x, y);
}

GameObject *FieldCellProxy::getObject() const {
    return mediator->getObjAt(x, y);
}
