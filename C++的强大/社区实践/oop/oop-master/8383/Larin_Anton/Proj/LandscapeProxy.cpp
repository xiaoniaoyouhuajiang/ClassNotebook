//
// Created by anton on 3/3/20.
//

#include "LandscapeProxy.h"

#include "Mediator.h"

LandscapeProxy::LandscapeProxy(Mediator *mediator, int x, int y) : mediator(mediator), x(x), y(y) {}


int LandscapeProxy::getOrd(UnitDevotion side) const {
    return mediator->getOrdAt(x, y, side);
}

int LandscapeProxy::getGirdle() const {
    return mediator->getGirdleAt(x, y);
}

UnitDevotion LandscapeProxy::getColor() {
    return mediator->getColorAt(x, y);
}
