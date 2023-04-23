#include "Base.h"

Base::Base(int limit)
{
    health.set(1000);
    armor.set(1000, true);
    damage.set(20,1);
    UnitsOnBase_['C'] = 0;
    UnitsOnBase_['A'] = 0;
    UnitsOnBase_['W'] = 0;
    UnitsOnBase_['M'] = 0;
    UnitsOnBase_['K'] = 0;
    UnitsOnBase_['S'] = 0;
    this->limit_ = limit;
    this->unitsOnBase_ = 0;
    this->unitsInGame_ = 0;
}

Object *Base::createBase() {
    auto base_ = new Base(15);
    base_->id_ = 'B';
    return base_;
}

void Base::createUnit(char id)
{
    if (unitsOnBase_ != limit_)
    {
        UnitsOnBase_[id] += 1;
        unitsOnBase_ ++;
    }
}

Object *Base::getUnit(char id, int quantity) {
    //if (quantity > UnitsOnBase_[id]) return nullptr;
    UnitsOnBase_[id] -= quantity;
    unitsInGame_ += quantity;
    switch(id)
    {
        case 'C':
            return fabric_.createCrossbowman();
        case 'A':
            return fabric_.createArcher();
        case 'W':
            return fabric_.createWitch();
        case 'M':
            return fabric_.createMage();
        case 'K':
            return fabric_.createKnight();
        case 'S':
            return fabric_.createSpearman();
        default:
            break;
    }
    return nullptr;
}
