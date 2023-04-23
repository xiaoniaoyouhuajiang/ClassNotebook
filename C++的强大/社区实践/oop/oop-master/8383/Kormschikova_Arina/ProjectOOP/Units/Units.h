
#ifndef Units_h
#define Units_h

#include "Interfaces.h"
#include "WeaponBehavior.h"


class Unit: public IUnits, IObserver{
public:
    int x,y;
    int hitPoint;
    int manaPoint;
    int magicResistance;
    int armor;
    char type;
    WeaponBehavior weapon;
    
    void showStat() override;
    void move(int x, int y, GameMap& map) override;
    void getDamage(int damage) override;
    void death() override;
    void update() override;
//    void deleteUnit() override;
//    bool createUnit(GameMap& map, int x, int y, char type) override;
    
    Unit();
};


class Rogue: public Unit{
public:
    void update();
    Rogue();
};

class Ranger: public Rogue{
public:
    Ranger();
};

class Slayer: public Rogue{
public:
    Slayer();
};


class Mage: public Unit{
public:
    void update();
    Mage();
};

class BattleMage: public Mage{
public:
    BattleMage();
};


class Witch: public Mage{
public:
    Witch();
};


class Warrior: public Unit{
public:
    void update();
    Warrior();
};


class Paladin: public Warrior{
public:
    Paladin();
};


class LanceKnight: public Warrior{
public:
    LanceKnight();
    
};





#endif /* Units_h */
