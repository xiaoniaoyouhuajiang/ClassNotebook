#include "Unit/liveshield.h"


LiveShield::LiveShield(Mediator* mediator)
{
    armor = new HeavyArmor;
    weapon = new NoWeapon;
    health = HIGH_HEALTH_VALUE;
    coordinate = new Point2D;

    this->mediator = mediator;
}


LiveShield::~LiveShield()
{
    delete armor;
    delete weapon;
    delete coordinate;
}


void LiveShield::regeneration()
{
    this->health += NO_REGENERATION_ABILITY;
}


Unit* LiveShield::clone()
{
    LiveShield* liveShield = new LiveShield(this->mediator);
    liveShield->armor = this->armor->clone();
    liveShield->weapon = this->weapon->clone();
    liveShield->coordinate = this->coordinate->clone();

    return liveShield;
}


char LiveShield::draw()
{
    return 'L';
}
