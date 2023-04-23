//
// Created by anton on 2/25/20.
//

#include "Base.h"

#include "Observee.h"
//#include "GameObject.h"
/*
Base::Base(Field *field,) : field(field) {
    factory=new CommonFactory(field);
    unitCount = new int[(int)UnitClass::NO_CLASS];//Number of classes
}
*/
/*
Base::Base(Field *field, CommonFactory *factory, int unitLim) : field(field), factory(factory), unitLim(unitLim) {unitCount=0}



bool Base::createUnit(UnitClass _class,UnitDevotion devotion, int x, int y) {
    if(unitCount>=unitLim)return false;
    unitCount++;
    auto unit = factory->createUnit(_class, devotion,x,y);
    field->setAt(*unit, x,y);
    return true;
}

int Base::getUnitLim() const {
    return unitLim;
}

void Base::setUnitLim(int unitLim) {
    Base::unitLim = unitLim;
}
*/

bool Base::addObservee(Observee *observee) {
    if (observees.count(observee))return false;
    observees.insert(observee);
    return true;
}

bool Base::removeObservee(Observee *observee) {
    if (!observees.count(observee))return false;
    observees.erase(observee);
    return true;
}
