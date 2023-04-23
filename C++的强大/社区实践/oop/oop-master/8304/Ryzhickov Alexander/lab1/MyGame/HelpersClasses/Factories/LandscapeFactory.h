//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_LANDSCAPEFACTORY_H
#define MYGAME_LANDSCAPEFACTORY_H


#include "../Landscapes/FieldLandscape.h"
#include "../Landscapes/ForestLandscape.h"
#include "../Landscapes/MountainLandscape.h"

class LandscapeFactory {
private:
    FieldLandscape *fieldLandscape;
    ForestLandscape *forestLandscape;
    MountainLandscape *mountainLandscape;
public:
    LandscapeFactory();
    ~LandscapeFactory();
    FieldLandscape *getFieldLandscape() const;
    ForestLandscape *getForestLandscape() const;
    MountainLandscape *getMountainLandscape() const;
};


#endif //MYGAME_LANDSCAPEFACTORY_H
