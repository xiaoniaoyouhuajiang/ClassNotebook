#include "unit.h"

Unit::Unit()
{

}

void Unit::setName(std::string name)
{
    this->name = name;
}

void Unit::setArmyType(std::string armyType)
{
    this->armyType = armyType;
}

void Unit::setAttributes(int armor, int health, int attack)
{
    *(this->attributes) = { armor, health, attack };
}

std::string Unit::getName()
{
    return this->name;
}

std::string Unit::getArmyType()
{
    return this->armyType;
}

int Unit::getArmor()
{
    return attributes->armor;
}

int Unit::getAttack()
{
    return attributes->attack;
}

int Unit::getHealth()
{
    return attributes->health;
}

void Unit::armorAdd(int numb)
{
    attributes->armor += numb;
}

void Unit::attackAdd(int numb)
{
    attributes->attack += numb;
}

void Unit::healthAdd(int numb)
{
    attributes->health += numb;
}

void Unit::deapth()
{
    this->notify();
}

void Unit::getDamage(int numb)
{
    this->attributes->health -= numb;
    std::cout << "Unit is damaged\n";
    if (this->attributes->health <= 0){
        this->deapth();
        std::cout << "Unit died\n";
    }
}
