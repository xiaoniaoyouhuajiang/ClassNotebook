//
// Created by Mila on 15.04.2020.
//

#include "LandscapeFactory.h"

Swamp *LandscapeFactory::getLandscapeSwamp() {
    return swamp;
}

Glade *LandscapeFactory::getLandscapeGlade() {
    return glade;
}

Abyss *LandscapeFactory::getLandscapeAbyss() {
    return abyss;
}

LandscapeFactory::LandscapeFactory() {
    swamp = new Swamp();
    glade = new Glade();
    abyss = new Abyss();
}

LandscapeFactory::~LandscapeFactory() {
   //delete swamp;
  //  delete (glade);
    //delete (abyss);

}
