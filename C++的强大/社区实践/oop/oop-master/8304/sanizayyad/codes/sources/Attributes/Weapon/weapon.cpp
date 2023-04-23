#include "weapon.hpp"

void Weapon::doCopy(const Weapon& weapon)
{
    this->damage = weapon.damage;
    this->distance = weapon.distance;
}

void Weapon::getWeaponInfo()
{
       std::cout<< "Attack Skills: ";
        std::cout<< "\n    Weapon Type: " << weaponType;
        std::cout<< "\n    Weapon Damage: " << damage;
        std::cout<< "\n    Weapon Distance: " << distance;
}
