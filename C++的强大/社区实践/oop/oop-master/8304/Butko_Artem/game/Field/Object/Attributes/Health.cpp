



#include "Health.h"

void Health::set(int health)
{
    maxHealth_ = health;
    health_ = health;
    isDead = false;
}

int Health::get()
{
    return health_;
}

void Health::actDamaged(size_t damage)
{
    if (health_ - damage < 0 || isDead)
        isDead = true;
    else
        health_ -= damage;
}

void Health::actHealed(size_t heal)
{
    if (!isDead)
        health_ += heal;
    if (health_ > maxHealth_)
        health_ = maxHealth_;
}
