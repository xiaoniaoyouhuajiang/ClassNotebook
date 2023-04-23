//
// Created by anton on 5/9/20.
//

#include "GameObject.h"

bool GameObject::isToBeRemoved() const {
    return toBeRemoved;
}

void GameObject::setToBeRemoved(bool toBeRemoved) {
    GameObject::toBeRemoved = toBeRemoved;
}

GameObject::GameObject(int x, int y, bool toBeRemoved, Devotion devotion, ObjectType objectType,
                       CommonClass objectClass,
                       int health, int armour, float dmgmul) : x(x), y(y), toBeRemoved(toBeRemoved), devotion(devotion),
                                                vitality(health,armour,dmgmul,this), objectType(objectType),objectClass(objectClass) {}

std::pair<int, int> GameObject::getCoords() {
    return {x,y};
}

void GameObject::setCoords(int x, int y) {
    this->x = x;
    this->y = y;
}
void GameObject::setCoords(std::pair<int,int> coords) {
    this->x = coords.first;
    this->y = coords.second;
}

Vitality &GameObject::getVitality() {
    return vitality;
}

Devotion GameObject::getDevotion() const {
    return devotion;
}

void GameObject::setMediator(const std::shared_ptr<Mediator> &mediator) {
    GameObject::mediator = mediator;
}

const std::shared_ptr<Mediator> &GameObject::getMediator() const {
    return mediator;
}

GameObjectFlyWeight * GameObject::getFlyWeight() {
    return flyWeight;
}

void GameObject::setFlyWeight(GameObjectFlyWeight *flyWeight) {
    GameObject::flyWeight = flyWeight;
}
