#include "Unit/dwarf.h"


Dwarf::Dwarf(Mediator* mediator)
{
    armor = new LightArmor;
    weapon = new Ax;
    health = HIGH_HEALTH_VALUE;
    coordinate = new Point2D;

    this->mediator = mediator;
}


Dwarf::~Dwarf()
{
    delete armor;
    delete weapon;
    delete coordinate;
}


void Dwarf::regeneration()
{
    this->health += HIGH_REGENERATION_ABILITY;
}


Unit* Dwarf::clone()
{
    Dwarf* dwarf = new Dwarf(this->mediator);
    dwarf->armor = this->armor->clone();
    dwarf->weapon = this->weapon->clone();
    dwarf->coordinate = this->coordinate->clone();

    return dwarf;
}


char Dwarf::draw()
{
    return 'G';
}
