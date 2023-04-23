#include "poison.h"

DrinkPoison::DrinkPoison(Poison* pos):poison(pos)
{

}

void DrinkPoison::operator +=(Unit &unit)
{
    poison->use(unit);
}

DrinkPoison::~DrinkPoison()
{
    delete poison;
}

void Covid19::use(Unit &unit)
{
    unit.getAttributes()->setHealth(unit.getAttributes()->getHealth()-19);
}

void Covid37::use(Unit &unit)
{
     unit.getAttributes()->setHealth(unit.getAttributes()->getHealth()-37);
}

string DrinkPoison::getType()const{
    return "neutral";
}


string DrinkPoison::characteristic()
{
    return "DrinkPoison";
}
