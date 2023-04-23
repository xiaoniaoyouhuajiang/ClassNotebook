#include "mediator.h"

Mediator::Mediator(GameField* field)
{
    this->field = field;
}

bool Mediator::attack(Unit* unit, int xx, int yy)
{
    if (xx >= 0 && yy >= 0 && xx <= field->x - 1 && yy <= field->y - 1){
        if (field->pointsMap[yy][xx]->base){
            if (field->pointsMap[yy][xx]->base->getDamage(unit->getAttack())){
                std::cout << "The base is destroyed!\n";
                return true;
            }
            std::cout << "Base was damaged!\n";
            return false;
        }
        else if (field->pointsMap[yy][xx]->unit){
            field->pointsMap[yy][xx]->unit->getDamage(unit->getAttack());
            LoggerProxy::unitDamage(field->pointsMap[yy][xx]->unit, xx, yy);
        }
        else{
            std::cout << "There is no one to attack\n";
        }
    }
    else {
        std::cout << "Wrong direction of attack\n";
    }
    return 0;
}

void Mediator::setMediator(Unit* unit)
{
    unit->setMediator(this);
}

void Mediator::updateField(GameField *field)
{
    this->field = field;
}
