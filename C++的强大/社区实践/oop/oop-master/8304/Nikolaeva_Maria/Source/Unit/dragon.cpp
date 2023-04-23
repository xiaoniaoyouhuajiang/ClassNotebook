#include "Unit/dragon.h"


Dragon::Dragon(Mediator* mediator)
{
    armor = new NoArmor;
    weapon = new FireBall;
    health = HIGH_HEALTH_VALUE;
    coordinate = new Point2D;

    this->mediator = mediator;
}


Dragon::~Dragon()
{
    delete armor;
    delete weapon;
    delete coordinate;
}


void Dragon::regeneration()
{
    this->health += LOW_REGENERATION_ABILITY;
}


Unit* Dragon::clone()
{
    Dragon* dragon = new Dragon(this->mediator);
    dragon->armor = this->armor->clone();
    dragon->weapon = this->weapon->clone();
    dragon->coordinate = this->coordinate->clone();

    return dragon;
}


char Dragon::draw()
{
    return 'D';
}
