#include "Mediator.h"

Mediator::Mediator(Field* field):field(field){}


void Mediator::attack(Unit* unit, int x, int y){
    if (x < 0 || y < 0 || x >= field->lenghtX || y >= field->lengthY){
        std::cout << "Impossible to attack in this area" << std::endl;
        return;
    }

    if (field->mapCell[y][x]->base != nullptr){
        field->mapCell[y][x]->base->wasAttack(unit->condition.attack);
        field->adapter->unitAttackBase(unit->name, field->mapCell[y][x]->base->numberBase);
    }

    else if (field->mapCell[y][x]->unit != nullptr){
        field->adapter->unitAttackUnit(unit->name, field->mapCell[y][x]->unit->name);
        field->mapCell[y][x]->unit->wasAttack(unit->condition.attack);
    }

    else{
        std::cout << "No attack, cell empty" << std::endl;
    }
}

void Mediator::setField(Field* field){
    this->field = field;
}