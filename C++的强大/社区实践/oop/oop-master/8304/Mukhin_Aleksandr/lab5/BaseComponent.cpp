#include "BaseComponent.h"
#include <iostream>

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

std::ostream& operator<<(std::ostream& out, const BaseComponent& component) {
    out << component.get_health() << std::endl;
    out << component.get_attack() << std::endl;
    out << component.get_intelligence() << std::endl;
    return out;
}

void BaseComponent::set_params(int health, int attack, int intelligence) {
    this->defense.set(health);
    this->attack.set(attack);
    this->intelligence = intelligence;
}
