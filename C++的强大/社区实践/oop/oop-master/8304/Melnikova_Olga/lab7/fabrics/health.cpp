#include "health.h"

Health::Health(Object* obj)
{
    if(typeid(*obj) == typeid(Archer) || typeid(*obj) == typeid(CrossBowMan) || typeid(*obj) == typeid(Knight) || typeid(*obj) == typeid(SpearMan)){
        _health = LIGHT_HEALTH;
    }
    if(typeid(*obj) == typeid(HeavyRider) || typeid(*obj) == typeid(LightRider)){
        _health = MEDIUM_HEALTH;
    }
    if(typeid(*obj) == typeid(Base)){
        _health = HEAVY_HEALTH;
    }
}
