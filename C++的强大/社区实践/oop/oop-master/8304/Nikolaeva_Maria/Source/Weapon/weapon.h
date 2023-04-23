#ifndef WEAPON_H
#define WEAPON_H

#include <cstring>


constexpr size_t SWORD_ATTACK_DISTANCE = 2;
constexpr size_t AX_ATTACK_DISTANCE  = 1;
constexpr size_t BOW_ATTACK_DISTANCE = 5;
constexpr size_t FIRE_BALL_ATTACK_DISTANCE  = 4;
constexpr size_t CLAWS_ATTACK_DISTANCE = 1;
constexpr size_t NO_ATTACK_DISTANCE = 0;

constexpr size_t FIRE_BALL_DAMAGE = 4;
constexpr size_t SWORD_DAMAGE  = 2;
constexpr size_t  BOW_DAMAGE = 1;
constexpr size_t  AX_DAMAGE = 1;
constexpr size_t  CLAWS_DAMAGE = 1;
constexpr size_t NO_DAMAGE = 0;


class Weapon
{
public:
    virtual ~Weapon() = default;

    virtual size_t getDamage() const = 0;

    virtual size_t getDistance() const = 0;

    virtual Weapon* clone() = 0;

protected:
    size_t damage;
    size_t distance;
};

#endif // WEAPON_H
