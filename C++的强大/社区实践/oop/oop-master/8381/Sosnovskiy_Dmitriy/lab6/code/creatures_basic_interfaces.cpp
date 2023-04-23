#include "creatures_basic_interfaces.h"

void IUnit::commitAttack(ICreature* attackedCreature)
{
    int damage = this->damage->getValue() + this->damage->getBonus();

    attackedCreature->takeDamage(damage);
}
