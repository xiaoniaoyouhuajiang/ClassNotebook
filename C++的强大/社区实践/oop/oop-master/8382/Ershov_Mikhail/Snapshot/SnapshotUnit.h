#pragma once

#include <iostream>

using namespace std;

class SnapshotUnit
{
public:
    SnapshotUnit(string name, int damage, int health, int armor, unsigned x, unsigned y);
    string getName() const;
    int getArmor() const;
    int getHealth() const;
    int getDamage() const;
    unsigned getX() const;
    unsigned getY() const;

private:
    string name;
    int health;
    int armor;
    int damage;
    unsigned x;
    unsigned y;
};
