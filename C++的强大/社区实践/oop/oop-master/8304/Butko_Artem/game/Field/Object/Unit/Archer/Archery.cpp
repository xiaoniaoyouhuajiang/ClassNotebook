



#include "Archery.h"

Archery::Archery(int health, int damage, int range, int armor, char id)
{
    this->health.set(health);
    this->damage.set(damage, range);
    this->armor.set(armor, false);
    this->id_ = id;
}

void Archery::regeneration(int heal)
{
    this->health.actHealed(heal);
}

void Archery::selfDamage(int damage)
{
    this->health.actDamaged(damage + 15);
}
