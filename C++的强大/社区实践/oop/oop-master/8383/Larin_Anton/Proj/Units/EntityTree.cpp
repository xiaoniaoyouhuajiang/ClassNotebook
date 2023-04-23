//
// Created by anton on 3/4/20.
//

#include "EntityTree.h"

wchar_t EntityTree::toChar() {
    return 'T';
}

bool EntityTree::die(const GameObject &src, GameObject &dst) {
    return GameObject::die(src, dst);
}

GameObject &EntityTree::operator+=(const LandscapeProxy &b) {
    return *this;
}

GameObject &EntityTree::operator+=(const FieldCellProxy &b) {
    this->operator+=(b.getLandscape());
    return *this;
}

GameObject &EntityTree::operator-=(const GameObject &b) {
    return *this;
}

EntityTree::EntityTree() {}

bool EntityTree::isValidStep(int x, int y) {
    return false;
}

bool EntityTree::step(int x, int y) {
    return false;
}

UnitClass EntityTree::getUnitClass() const {
    return UnitClass::TREE;
}
