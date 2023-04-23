#pragma once

#include "Object/Object.h"
#include "Game/Game.h"

class Player;
class Base;


class IUnit : public Object
{
    friend class HealOffice;
    friend class DamageOffice;
    friend class ArmorOffice;
    friend class MovementOffice;
    friend class Game;

public:
    IUnit();

    uint16_t getGroupType() override;
    virtual uint16_t getUnitClass() = 0;

    virtual Player* getPlayer() = 0;
    virtual Base* getBase() = 0;

    virtual uint16_t getMaxHealth() = 0;
    virtual uint16_t getHealth() = 0;
    virtual uint16_t getAttack() = 0;
    virtual uint16_t getAttackRadius() = 0;
    virtual uint16_t getArmor() = 0;
    virtual uint16_t getMaxMovePoints() = 0;
    virtual uint16_t getMovePoints() = 0;

    virtual uint16_t giveDamage(IUnit* enemy) = 0;
    virtual uint16_t giveDamage(Base* enemy) = 0;
    virtual bool takeDamage(uint16_t damage) = 0;

    bool move(Point point);
    void attack(IUnit* defender);
    void attack(Base* defender);
    void unite(IUnit* passive);

    virtual void setAttacked() = 0;
    virtual void unsetAttacked() = 0;
    virtual bool checkAttacked() = 0;

protected:
    virtual void setPoint(Point point) = 0;
    virtual void setMovePoints(uint16_t points) = 0;

    virtual void smallHeal(uint16_t healSize = 10) = 0;
    virtual void fullHeal() = 0;
    virtual void attackModification(int16_t modSize) = 0;
    virtual void armorModification(int16_t modSize) = 0;
    virtual void renewMovePoints() = 0;
};
