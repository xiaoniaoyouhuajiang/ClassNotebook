#include "LandscapeProxy.h"


LandscapeProxy::LandscapeProxy(Landscape* landscape) {
    this->landscape = landscape;
}

LandscapeProxy::~LandscapeProxy() {
    delete landscape;
    landscape = nullptr;
}


uint16_t LandscapeProxy::getObjectType() {
    if (landscape != nullptr) {
        log();
        return landscape->getObjectType();
    }
    return LAND;
}

Point LandscapeProxy::getPoint() {
    if (landscape != nullptr) {
        log();
        return landscape->getPoint();
    }
    return Point(0, 0);
}


bool LandscapeProxy::movementAccess() {
    if (landscape != nullptr) {
        log();
        return landscape->movementAccess();
    }
    return false;
}

int16_t LandscapeProxy::getMovementCost() {
    if (landscape != nullptr) {
        log();
        return landscape->getMovementCost();
    }
    return 0;
}


void LandscapeProxy::log() {
    // Логгирование - это четвертая лаба, а прокси - вторая. Все еще впереди!
}
