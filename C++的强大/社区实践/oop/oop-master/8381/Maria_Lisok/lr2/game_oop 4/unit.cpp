#include "unit.h"

string Unit::characteristic(){
    string chr{};
    chr.append("Main properties "+this->name
               +"\nHealth: "+to_string(attributes->getHealth())
               +"\nArmor: "+to_string(attributes->getArmor())
               +"\nAttack: "+to_string(attributes->getArmor()));
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

