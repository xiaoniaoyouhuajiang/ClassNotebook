#include "Unit/swordsman.h"


Swordsman::Swordsman(Mediator* mediator)
{
    armor = new LightArmor;
    weapon = new Sword;
    health = LOW_HEALTH_VALUE;
    coordinate = new Point2D;

    this->mediator = mediator;
}


Swordsman::~Swordsman()
{
    delete armor;
    delete weapon;
    delete coordinate;
}


void Swordsman::regeneration()
{
    this->health += LOW_REGENERATION_ABILITY;
}


Unit* Swordsman::clone()
{
    Swordsman* swordsman = new Swordsman(this->mediator);
    swordsman->armor = this->armor->clone();
    swordsman->weapon = this->weapon->clone();
    swordsman->coordinate = this->coordinate->clone();

    return swordsman;
}


char Swordsman::draw()
{
    return 'S';
}
