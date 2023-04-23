//
// Created by Artem Butko on 08/05/2020.
//

#include "Health.h"

void Health::set(int health)
{
    this->health_ = health;
    this->maxHealth_ = health;
}

int Health::get()
{
    return this->health_;
}

void Health::actDamaged(int damage)
{
    this->health_ -= damage;
    if (this->health_ <= 0) this->isDead = true;
}

void Health::actHealed(int heal)
{
    if (!this->isDead)
    {
        this->health_ += heal;
        if (this->health_ > this->maxHealth_)
            this->health_ = this->maxHealth_;
    }
}



