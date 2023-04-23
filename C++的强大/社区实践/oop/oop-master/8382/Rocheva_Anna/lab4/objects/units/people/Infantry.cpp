#include "Infantry.hpp"


Unit & Infantry::operator+=(NeutralObject &object) {
    if (object.getObjName() == HOSPITAL){
        auto *context = new UnitContext(new HospitalStrategyPeople);
        context->changeUnitsAttributes(*this);
    }
    else if (object.getObjName() == TRAIN){
        auto *context = new UnitContext(new TrainStrategyPeople);
        context->changeUnitsAttributes(*this);
    }
    else if (object.getObjName() == BAR){
        auto *context = new UnitContext(new BarStrategy);
        context->changeUnitsAttributes(*this);
    }
    else if (object.getObjName() == SHOP){
        auto *context = new UnitContext(new ShopStrategyOther);
        context->changeUnitsAttributes(*this);
    }
    return *this;
}
