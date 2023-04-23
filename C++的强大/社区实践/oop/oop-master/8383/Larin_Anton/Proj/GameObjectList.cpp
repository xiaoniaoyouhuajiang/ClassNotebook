//
// Created by anton on 3/2/20.
//

#include "GameObjectList.h"

GameObjectList::GameObjectList(GameObjectList &src) {
    this->insert(this->begin(), src.begin(), src.end());

}

GameObjectList::GameObjectList(std::list<GameObject *> lst) {
    this->insert(this->begin(), lst.begin(), lst.end());
}

GameObjectList &GameObjectList::ofDevotion(UnitDevotion unitDevotion, bool inclusive) {
    for (auto it = this->begin(); it != this->end(); it++) {
        if (((*it)->getUnitDevotion() == unitDevotion) != inclusive) {
            this->erase(it);
        }
    }
    return *this;
}

GameObjectList &GameObjectList::ofClass(UnitClass unitClass, bool inclusive) {
    for (auto it = this->begin(); it != this->end(); it++) {
        if (((*it)->getUnitClass() == unitClass) != inclusive) {
            this->erase(it);
        }
    }
    return *this;
}

GameObjectList &GameObjectList::ofType(UnitType unitType, bool inclusive) {
    for (auto it = this->begin(); it != this->end(); it++) {
        if ((GameObject::classToType((*it)->getUnitClass()) == unitType) != inclusive) {
            this->erase(it);
        }
    }
    return *this;
}
