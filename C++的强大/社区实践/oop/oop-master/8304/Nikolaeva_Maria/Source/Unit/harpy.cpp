#include "Unit/harpy.h"


Harpy::Harpy(Mediator* mediator)
{
    armor = new NoArmor;
    weapon = new Claws;
    health = LOW_HEALTH_VALUE;
    coordinate = new Point2D;

    this->mediator = mediator;
}


Harpy::~Harpy()
{
    delete armor;
    delete weapon;
    delete coordinate;
}


void Harpy::regeneration()
{
    this->health += HIGH_REGENERATION_ABILITY;
}


Unit* Harpy::clone()
{
    Harpy* harpy = new Harpy(this->mediator);
    harpy->armor = this->armor->clone();
    harpy->weapon = this->weapon->clone();
    harpy->coordinate = this->coordinate->clone();

    return harpy;
}


char Harpy::draw()
{
    return 'H';
}
