//
// Created by Mila
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
