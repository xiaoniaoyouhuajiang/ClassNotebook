#ifndef UNIT_H
#define UNIT_H

#include "Armor/armor.h"
#include "Armor/lightarmor.h"
#include "Armor/heavyarmor.h"
#include "Armor/noarmor.h"

#include "Weapon/weapon.h"
#include "Weapon/ax.h"
#include "Weapon/bow.h"
#include "Weapon/claws.h"
#include "Weapon/fireball.h"
#include "Weapon/sword.h"
#include "Weapon/noweapon.h"

#include "point2d.h"
#include "mediator.h"
#include "IDrawable.h"
#include "IRegeneration.h"


constexpr size_t HIGH_REGENERATIVE_ABILITI_VALUE = 2;
constexpr size_t LOW_REGENERATIVE_ABILITI_VALUE = 1;
constexpr size_t HIGH_HEALTH_VALUE = 2;
constexpr size_t LOW_HEALTH_VALUE = 1;
constexpr size_t HIGH_REGENERATION_ABILITY = 4;
constexpr size_t LOW_REGENERATION_ABILITY = 1;
constexpr size_t NO_REGENERATION_ABILITY = 1;


class Unit : public IRegeneration,
        public IDrawable
{
public:
    explicit Unit() = default;
    virtual ~Unit() = default;

    Armor* getArmor() const;
    bool setArmor(Armor* armor);

    Weapon* getWeapon() const;
    bool setWeapon(Weapon* weapon);

    Point2D getCoordiante() const;
    bool setCoordinate(Point2D* point);

    size_t getHealth();

    virtual bool move(int dx, int dy) = 0;
    virtual bool isFlying() = 0;

    virtual Unit* clone() = 0;

protected:
    Armor* armor;
    Weapon* weapon;
    size_t health;
    Point2D* coordinate;
    Mediator* mediator;
};

#endif // UNIT_H
