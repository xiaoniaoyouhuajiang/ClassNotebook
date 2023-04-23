//
// Created by Alex on 22.03.2020.
//

#ifndef GAME_LANDSCAPEFACTORY_H
#define GAME_LANDSCAPEFACTORY_H


#include "../Landscapes/FieldLandscape.h"
#include "../Landscapes/ForestLandscape.h"
#include "../Landscapes/MountainsLandscape.h"

class LandscapeFactory {
    private:
        FieldLandscape *fieldLandscape;
        ForestLandscape *forestLandscape;
        MountainsLandscape *mountainLandscape;
    public:
        LandscapeFactory();
        ~LandscapeFactory();
        FieldLandscape *getFieldLandscape() const;
        ForestLandscape *getForestLandscape() const;
        MountainsLandscape *getMountainLandscape() const;
};


#endif //GAME_LANDSCAPEFACTORY_H
