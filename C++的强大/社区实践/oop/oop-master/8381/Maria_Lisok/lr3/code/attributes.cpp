#include "attributes.h"

int Attributes::getHealth() const
{
    return health;
}

void Attributes::setHealth(int value)
{
    health = value;
}

int Attributes::getArmor() const
{
    return armor;
}

void Attributes::setArmor(int value)
{
    armor = value;
}

int Attributes::getAttack() const
{
    return attack;
}

void Attributes::setAttack(int value)
{
    attack = value;
}

Attributes::Attributes()
{
    setArmor(0);
    setAttack(0);
    setHealth(0);
}
void Attributes::setAllAttributes(int health, int armor, int attack){
    setArmor(armor);
    setHealth(health);
    setAttack(attack);
}
