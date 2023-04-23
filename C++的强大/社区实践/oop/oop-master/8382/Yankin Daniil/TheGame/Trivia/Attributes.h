#pragma once

#include <cstdint>


class Health
{
public:
    Health();
    Health(uint16_t maxHealth, uint16_t health);

    void setMaxHealth(uint16_t maxHealth);
    void setHealth(uint16_t health);
    uint16_t getMaxHealth() const;
    uint16_t getHealth() const;

private:
    uint16_t maxHealth;
    uint16_t health;
};


class Strength
{
public:
    Strength();
    Strength(uint16_t strength, uint16_t radius);

    void setStrength(uint16_t strength);
    void setRadius(uint16_t radius);
    uint16_t getStrength() const;
    uint16_t getRadius() const;

private:
    uint16_t strength;
    uint16_t radius;
};


class Armor
{
public:
    Armor();
    Armor(uint16_t armor);

    void setArmor(uint16_t armor);
    uint16_t getArmor() const;

private:
    uint16_t armor;
};


class MovePoints {
public:
    MovePoints();
    MovePoints(uint16_t maxMovePoints, uint16_t movePoints);

    void setMaxMovePoints(uint16_t maxMovePoints);
    void setMovePoints(uint16_t movePoints);
    uint16_t getMaxMovePoints() const;
    uint16_t getMovePoints() const;

private:
    uint16_t maxMovePoints;
    uint16_t movePoints;
};
