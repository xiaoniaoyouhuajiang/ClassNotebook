



#include "Mages.h"

Mages::Mages(int health, int damage, int range, int armor, char id)
{
    this->health.set(health);
    this->damage.set(damage, range);
    this->armor.set(armor, false);
    this->id_ = id;
}

void Mages::regeneration(int heal)
{
    this->health.actHealed(heal + 10);
}

void Mages::selfDamage(int damage)
{
    this->health.actDamaged(damage + 10 );
}
