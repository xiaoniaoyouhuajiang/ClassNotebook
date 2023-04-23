//
// Created by Alex on 22.03.2020.
//

#include "LandscapeFactory.h"

LandscapeFactory::LandscapeFactory() {
    fieldLandscape = new FieldLandscape();
    forestLandscape = new ForestLandscape();
    mountainLandscape = new MountainsLandscape();
}

FieldLandscape *LandscapeFactory::getFieldLandscape() const {
    return fieldLandscape;
}

ForestLandscape *LandscapeFactory::getForestLandscape() const {
    return forestLandscape;
}

MountainsLandscape *LandscapeFactory::getMountainLandscape() const {
    return mountainLandscape;
}

LandscapeFactory::~LandscapeFactory() {
    delete fieldLandscape;
    delete forestLandscape;
    delete mountainLandscape;
}