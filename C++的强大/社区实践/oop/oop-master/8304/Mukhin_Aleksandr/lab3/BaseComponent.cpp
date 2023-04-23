#include "BaseComponent.h"

void BaseComponent::set_mediator(BaseMediator* med) {
    mediator = med;
}

int BaseComponent::get_health() const {
    return defense.get_health();
}

int BaseComponent::get_attack() const {
    return attack.get_attack();
}

int BaseComponent::get_intelligence() const {
    return intelligence;
}

void BaseComponent::change_health(int value) {
    defense.change(value);
}

void BaseComponent::change_attack(int value) {
    attack.change(value);
}

void BaseComponent::change_intelligence(int value) {
    intelligence += value;
}
