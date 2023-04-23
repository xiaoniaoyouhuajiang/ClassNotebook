#include "landscapefabric.h"

LandscapeFabric::LandscapeFabric(){}
LandscapeFabric::~LandscapeFabric(){}

Glade* LandscapeFabric::glade(){
    Glade* newGlade = new Glade();
    Damage setDamage(newGlade);
    newGlade->damage = setDamage._damage;
    return newGlade;
}
Swamp* LandscapeFabric::swamp(){
    Swamp* newSwamp = new Swamp();
    Damage setDamage(newSwamp);
    newSwamp->damage = setDamage._damage;
    return newSwamp;
}
Cliff* LandscapeFabric::cliff(){
    Cliff* newCliff = new Cliff();
    Damage setDamage(newCliff);
    newCliff->damage = setDamage._damage;
    return newCliff;
}
