//
// Created by Artem Butko on 08/05/2020.
//

#include "Magician.h"

Magician::Magician(int health, int mana, int damage, int damageRange, int cost, int moveRange, char id)
{
    this->health.set(health);
    this->mana.set(mana);
    this->damage.set(damage, damageRange, cost);
    this->range.set(moveRange);
    this->id = id;
}

void Magician::regeneration(int health, int mana)
{
    this->health.actHealed(health);
    this->mana.actRecovered(mana);
}

void Magician::makeDamage(int damage, Object *other)
{
    /* TODO вычисление расстояния до другого объекта и нанесение ему урона (если он находится в радиусе действия атаки). */
    //pow(other->x, 2) + pow(other->y, 2);
    other->health.actDamaged(this->damage.getDamage());
    this->mana.actReduced(this->damage.getCost());
}