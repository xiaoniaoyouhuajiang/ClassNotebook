#include "unitfactory.h"

UnitFactory::UnitFactory() {}
Unit* UnitFactory::createUnit(char name, int x, int y) {
    switch(name) {
        case 'P' : return priestCreator.create(x, y); break;
        case 'N' : return necroCreator.create(x,y); break;
        case 'Y' : return yoyoCreator.create(x,y); break;
        case 'K' : return katanaCreator.create(x,y); break;
        case 'S' : return slingermanCreator.create(x,y); break;
        case 'C': return crossbowCreator.create(x,y); break;
        default:
            std::cout << "No such type of unit!" << std::endl;
            return nullptr;
    }
}
