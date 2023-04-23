#include "fireball.h"


FireBall::FireBall()
{
    damage = FIRE_BALL_DAMAGE;
    distance = FIRE_BALL_ATTACK_DISTANCE;
}


size_t FireBall::getDamage() const
{
    return this->damage;
}


size_t FireBall::getDistance() const
{
    return this->distance;
}


Weapon* FireBall::clone()
{
    FireBall* fireBall = new FireBall;
    fireBall->distance = this->distance;
    fireBall->damage = this->damage;

    return fireBall;
}
