



#include "Armor.h"

void Armor::set(int armor, bool exist)
{
    this->armor_ = armor;
    this->isExist = exist;
}

int Armor::get()
{
    return armor_;
}

void Armor::actDamaged(size_t damage)
{
    if (isExist)
    {
        armor_ -= damage;
        if (armor_ <= 0)
            isExist = false;
    }
}

