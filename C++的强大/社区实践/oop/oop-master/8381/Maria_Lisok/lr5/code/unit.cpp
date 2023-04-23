#include "unit.h"

string Unit::characteristic(){
    string chr{};
    chr.append("Main properties "+this->name
               +"\nHealth: "+to_string(attributes->getHealth())
               +"\nArmor: "+to_string(attributes->getArmor())
               +"\nAttack: "+to_string(attributes->getAttack()));
    return chr;
}
Unit::Unit(Unit& unit):name(unit.name), movable(unit.movable),
    attributes(unit.attributes), moveMediator(nullptr){}

Unit::~Unit(){
    delete moveMediator;
}
bool Unit::isMovable(){
    return movable;
}
string Unit::getType()const{
    return "unit";
}



void Unit::setAttackMediator(AttackMediator *value)
{
    attackMediator = value;
}

void Unit::attack(int x, int y)
{
    attackMediator->attack(this, x, y);
}

bool Unit::recieveAttack(Unit *u)
{
    Attributes* att = u->getAttributes();
    int armor = attributes->getArmor() - att->getAttack();
    if(armor < 0){
        attributes->setArmor(0);
        int health =  attributes->getHealth() - armor;
        if(health <= 0)
            return false;
        else{
            attributes->setHealth(health);
        }
    }else{
        attributes->setArmor(armor);
    }
    return true;
}

int Unit::getBaseNumber() const
{
    return baseNumber;
}

unsigned Unit::getX() const
{
    return x;
}

unsigned Unit::getY() const
{
    return y;
}

void Unit::setX(const unsigned &value)
{
    x = value;
}

void Unit::setY(const unsigned &value)
{
    y = value;
}

void Unit::setBaseNumber(int value)
{
    baseNumber = value;
}
void Unit::setMoveMediator(MoveMediator* value){
    moveMediator = value;
}

Attributes* Unit::getAttributes() const
{
    return attributes;
}

void Unit::setAttributesHealth(int health)
{
    attributes->setHealth(health);
}
void Unit::setAttributesArmor(int armor)
{
    attributes->setArmor(armor);
}
void Unit::setAttributesAttack(int attack)
{
    attributes->setAttack(attack);
}
void Unit::move(int x, int y){
    moveMediator->moveObj(this, x, y);
}

