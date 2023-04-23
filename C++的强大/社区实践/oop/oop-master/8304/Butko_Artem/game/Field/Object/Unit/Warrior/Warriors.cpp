#include "Warriors.h"

Warriors::Warriors(int health, int damage, int range, int armor, char id)
{
    this->health.set(health);
    this->damage.set(damage, range);
    this->armor.set(armor, true);
    this->id_ = id;
}

void Warriors::regeneration(int heal)
{
    this->health.actHealed(heal - 10);
}

void Warriors::selfDamage(int damage)
{
    this->health.actDamaged(damage - 10);
}

