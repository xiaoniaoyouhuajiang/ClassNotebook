//
// Created by Mila on 15.04.2020.
//

#ifndef UNTITLED_LANDSCAPEFACTORY_H
#define UNTITLED_LANDSCAPEFACTORY_H


#include "../Landscape/Swamp.h"
#include "../Landscape/Glade.h"
#include "../Landscape/Abyss.h"

class LandscapeFactory {
public:
    LandscapeFactory();

    virtual ~LandscapeFactory();

    Swamp* getLandscapeSwamp();
    Glade* getLandscapeGlade();
    Abyss* getLandscapeAbyss();

private:
    Swamp* swamp;
    Glade* glade;
    Abyss* abyss;

};


#endif //UNTITLED_LANDSCAPEFACTORY_H
