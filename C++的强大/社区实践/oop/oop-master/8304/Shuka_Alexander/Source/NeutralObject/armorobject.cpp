#include "armorobject.h"

using namespace unit;


ArmorObject::ArmorObject(const ArmorObject& object)
{
    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }
}


ArmorObject& ArmorObject::operator=(const ArmorObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> ArmorObject::clone() const
{
    return std::make_shared<ArmorObject>(*this);
}


char ArmorObject::draw() const
{
    return 'a';
}


void ArmorObject::selectStrategy(std::shared_ptr<Unit> unit)
{
    if (typeid (unit.get()) == typeid (Dragon)) {
        strategy = std::make_shared<DragonArmorUpStrategy>();
    }
    else if (typeid (unit.get()) == typeid (Thief)) {
        strategy = std::make_shared<ThiefArmorUpStrategy>();
    }
    else if (typeid (unit.get()) == typeid (Warrior)) {
        strategy = std::make_shared<WarriorArmorUpStrategy>();
    }
    else if (typeid (unit.get()) == typeid (Kamikadze)) {
        strategy = std::make_shared<KamikadzeArmorUpStrategy>();
    }
    else {
        strategy = std::make_shared<NoStrategy>();
    }
}
