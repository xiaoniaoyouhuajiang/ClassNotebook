#include "Base.h"

Base::Base() {
    this->setArmor(20);
    this->setHealth(3000);
    this->setPosition(0, 0);
    this->setDamage(0);
    this->setRange(0);
}

bool Base::create_unit(Field* field, Object* unit, int x, int y) {

    if(unit == nullptr) {
        std::cout << "If you want to delete an object use removeObject instead\n";
        return false;
    }
    if (currentQuantity + 1 <= maxQuantity) {
        if (field->getHead()[y - 1][x - 1].unit == nullptr) {

            subscribe(unit);
            field->landscape_interaction(unit, x - 1, y - 1);
            if(field->getHead()[y - 1][x - 1].neutral != nullptr) {
                (*field->getHead()[y - 1][x - 1].neutral)(dynamic_cast<Unit*>(unit));
            }

            field->getHead()[y - 1][x - 1].unit = unit;

            unit->setPosition(x, y);
        }

        else {
            std::cout << "This position is already taken by another object\n";
            return false;
        }
    }
    else {
        std::cout << "Base contains maximum quantity of units\n";
        return false;
    }
    return true;
}

void Base::setMaxQuantity(const int n) {
    this->maxQuantity = n;
}

int Base::getMaxQuantity() {
    return this->maxQuantity;
}

void Base::subscribe(Object * obj) {
    obj->IncreaseArmor(3);
    obj->IncreaseDmg(5);
    obj->actHealed(obj->getHealth() / 5);
    ++currentQuantity;
    warriors.push_back(obj);
}

void Base::unsubscribe(Object *obj) {
    auto it = std::find(warriors.begin(), warriors.end(), obj);
    if(it != warriors.end()){
        warriors.erase(it);
    }
    --currentQuantity;
}

Base* Base::clone() {
    auto tmp = new Base();

    tmp->setHealth(this->getHealth());

    tmp->setDamage(this->getDamage());

    tmp->setRange(this->getRange());

    tmp->setArmor(this->getArmor());

    return tmp;
}



