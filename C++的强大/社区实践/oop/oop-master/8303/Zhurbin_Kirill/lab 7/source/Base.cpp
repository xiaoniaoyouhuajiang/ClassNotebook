#include <iostream>
#include "Base.h"
#include "Field.h"
#include "FactorySoldier.h"
#include "FactoryShooter.h"
#include "FactoryTankman.h"

Base::Base(Field* field, int maxCountUnit, int health, int BaseX, int BaseY): maxCountUnit(maxCountUnit), health(health), countUnit(0), field(field), BaseX(BaseX), BaseY(BaseY), current(0) {
    this->compositUnit = new CompositUnit();
}

bool Base::createUnit(char name, Mediator* mediator, Adapter* adapter) {
    if (this->countUnit < this->maxCountUnit && (name == 'o' || name=='y' || name == 'k' || name == 's' || name == 'l' || name == 'h')) {
        Unit* unit;
        if (name == 'o')
            unit = FactorySoldier().createStrongUnit();
        else if (name == 'y')
            unit = FactorySoldier().createWeakUnit();
        else if (name == 'k')
            unit = FactoryShooter().createStrongUnit();
        else if (name == 's')
            unit = FactoryShooter().createWeakUnit();
        else if (name == 'l')
            unit = FactoryTankman().createWeakUnit();
        else if (name == 'h')
            unit = FactoryTankman().createStrongUnit();

        if (field->addUnit(unit, BaseX-1, BaseY)){}
        else if(field->addUnit(unit, BaseX-1, BaseY-1)){}
        else if(field->addUnit(unit, BaseX, BaseY-1)){}
        else if(field->addUnit(unit, BaseX+1, BaseY-1)){}
        else if(field->addUnit(unit, BaseX+1, BaseY)){}
        else if(field->addUnit(unit, BaseX+1, BaseY+1)){}
        else if(field->addUnit(unit, BaseX, BaseY+1)){}
        else if(field->addUnit(unit, BaseX-1, BaseY+1)){}
        else{
            delete(unit);
            return false;
        }


        unit->addObserver(this);
        unit->setMediator(mediator);
        unit->setAdapter(adapter);
        adapter->createUnit(unit);
        compositUnit->addUnit(unit);
        this->countUnit++;

        //if (unit->character == "shooter")
        //    unit->death();
        return true;
    }

}

bool Base::setUnit(char name, int unitX, int unitY, int health, int attack, int armor, Mediator* mediator, Adapter* adapter) {
    if (this->countUnit < this->maxCountUnit && (name == 'o' || name=='y' || name == 'k' || name == 's' || name == 'l' || name == 'h')) {
        Unit* unit;
        if (name == 'o')
            unit = FactorySoldier().createStrongUnit();
        else if (name == 'y')
            unit = FactorySoldier().createWeakUnit();
        else if (name == 'k')
            unit = FactoryShooter().createStrongUnit();
        else if (name == 's')
            unit = FactoryShooter().createWeakUnit();
        else if (name == 'l')
            unit = FactoryTankman().createWeakUnit();
        else if (name == 'h')
            unit = FactoryTankman().createStrongUnit();

        unit->condition.health = health;
        unit->condition.armor = armor;
        unit->condition.attack = attack;

        field->addUnit(unit, unitX, unitY);

        unit->addObserver(this);
        unit->setMediator(mediator);
        unit->setAdapter(adapter);
        compositUnit->addUnit(unit);
        this->countUnit++;

        return true;
    }

}

void Base::removeUnit(Unit *unit) {
    if (compositUnit->removeUnit(unit))
    {
        unit->removeObserver(this);
        field->removeUnit(unit);
        this->countUnit--;
    }

}

bool Base::isDestroyed(){
    return health <= 0;
}

bool Base::wasAttack(int damage){
    std::cout << "The base was attack" << std::endl;
    std::cout << "Health before attack: " << this-> health << std::endl;
    this->health -= damage;
    std::cout << "Health after attack: " << this-> health << std::endl;
    adapter->attackBase(this->numberBase);
}

int Base::getCapacityUnit(){
    return maxCountUnit - countUnit;
}

Unit* Base::getUnit(){
    if (current >= compositUnit->masUnit.size())
        current = 0;
    return compositUnit->masUnit[current++];
}

void Base::printUnit() {
    for (int i=0; i < this->compositUnit->masUnit.size(); i++) {
        std::cout << "\tUnit  " << this->compositUnit->masUnit[i]->name;
        std::cout << " x: " << field->findUnit(this->compositUnit->masUnit[i])->x << "  y: " << field->findUnit(this->compositUnit->masUnit[i])->y << "  health: " << field->findUnit(this->compositUnit->masUnit[i])->unit->condition.health << std::endl;
    }
}

void Base::update(SubjectObserve* subject) {
    this->removeUnit(static_cast<Unit *>(subject));
}

