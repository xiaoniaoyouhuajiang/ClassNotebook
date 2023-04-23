



#include "Damage.h"

void Damage::set(size_t damage, size_t range)
{
    this->damage_.first = damage;
    this->damage_.second = range;
}

std::pair<size_t, size_t> Damage::get()
{
    return damage_;
}

size_t Damage::getDamage()
{
    return damage_.first;
}

size_t Damage::getRange()
{
    return damage_.second;
}
