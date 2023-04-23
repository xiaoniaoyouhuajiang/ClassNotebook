#include <iostream>
#include "Base.h"
#include "Field.h"
#include "FactorySoldier.h"
#include "FactoryShooter.h"
#include "FactoryTankman.h"

Base::Base(Field* field, int maxCountUnit, int health, int BaseX, int BaseY): maxCountUnit(maxCountUnit), health(1000), countUnit(0), field(field), BaseX(BaseX), BaseY(BaseY) {
    this->compositUnit = new CompositUnit();
}

void Base::createUnit(char name) {
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
            return;
        }


        unit->addObserver(this);
        compositUnit->addUnit(unit);
        this->countUnit++;

        //if (unit->character == "shooter")
        //    unit->death();
    }
}

void Base::removeUnit(Unit *unit) {
    unit->removeObserver(this);
    field->removeUnit(unit);
    compositUnit->removeUnit(unit);
    this->countUnit--;

}

void Base::printUnit() {
    compositUnit->printUnit();
}

void Base::update(SubjectObserve* subject) {
    this->removeUnit(static_cast<Unit *>(subject));
}