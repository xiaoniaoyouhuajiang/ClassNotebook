#include "damage.h"

Damage::Damage(Landscape* obj)
{
    if(typeid(*obj) == typeid(Cliff)){
        _damage = HEAVY_DAMAGE;
    }
    if(typeid(*obj) == typeid(Glade)){
        _damage = NO_DAMAGE;
    }
    if(typeid(*obj) == typeid(Swamp)){
        _damage = MEDIUM_DAMAGE;
    }
}
