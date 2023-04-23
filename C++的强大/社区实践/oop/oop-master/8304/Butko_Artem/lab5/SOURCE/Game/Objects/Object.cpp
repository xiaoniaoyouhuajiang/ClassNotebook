//
// Created by Artem Butko on 08/05/2020.
//

#include "Object.h"

void Object::death()
{
    this->notice();
}

void Object::getInformation()
{
    std::cout << "------- OBJECT INFO ---------" <<  std::endl;
    std::cout << "Name of object : " << this->id << std::endl;
    std::cout << "Health :         " << this->health.get() << std::endl;
    std::cout << "Mana   :         " << this->mana.get() << std::endl;
    std::cout << "Damage :         " << this->damage.getDamage() << std::endl;
    std::cout << "Damage radius  : " << this->damage.getRange() << std::endl;
    std::cout << "_____________________________" << std::endl;
}
