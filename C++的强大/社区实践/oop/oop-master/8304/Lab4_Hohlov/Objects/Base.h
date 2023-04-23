
#ifndef UNTITLED13_BASE_H
#define UNTITLED13_BASE_H

#include "../Armor/Armor.h"
#include "GameObject.h"
#include "../Observers/UnitObserver.h"
#include "../Observers/BaseObserver.h"

#include "../Objects/Units/Unit.h"

#include <vector>
#include <iostream>
#include <algorithm>

class Base: public GameObject, public UnitObserver {

private:

    std::vector<BaseObserver*> baseObservers;

protected:

    void print(std::ostream &stream) const override;

public:

    Base(int health, Armor &armor): GameObject(ObjectType::BASE), health(health), armor(armor) {}
    bool addUnit(Unit *unit, Point position);
    void addObserver(BaseObserver *baseObserver);

    int getHealth(){ return health; }
    Armor& getArmor(){ return armor; }
    int getMaxObjectsCount(){ return maxObjectsCount; }

    template <typename T>
    T *createUnit(Point position);

    void onUnitAttack(Unit *unit, Unit *other) override;
    void onUnitMove(Unit *unit, Point p) override;
    void onUnitDestroy(Unit *unit) override;
    void onUnitDamaged(Unit *unit) override;
    void onUnitHeal(Unit *unit) override;

private:

    std::vector<Unit*> units;

    int health;
    const int maxObjectsCount = 5;
    Armor &armor;

};

template<typename T>
T *Base::createUnit(Point position) {
    if (units.size() < maxObjectsCount) {
        T *unit = new T();
        units.push_back(unit);
        unit->addObserver(this);

        for (auto bo:baseObservers) bo->onBaseNewUnitCreated(unit, position);
        game::log << "[Base] Unit created\n";

        return unit;
    } else{

        game::log << "[Base] Cannot create unit. Limit is exceeded.\n";
        return nullptr;

    }
}

#endif //UNTITLED13_BASE_H
