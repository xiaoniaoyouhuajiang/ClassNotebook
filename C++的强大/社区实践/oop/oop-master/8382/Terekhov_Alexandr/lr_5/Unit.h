#ifndef OOP_UNIT_H
#define OOP_UNIT_H

#include <ostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "NeutralObject.h"
#include "Logger.h"

class IDGenerator {
private:
    static int s_nextID;
public:
    static int getNextID();
};

class Unit : public AbstractObject {
protected:
    int health = 50;
    int damage;
    int armor;
    int id;
    bool isEnemy = true;
public:
    int getDamage() const;

    int getArmor() const;

    Unit(char pict, int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
    bool getIsEnemy() const;
    int getHealth() const;
    int getID() const;
    int giveDamage() const;
    int takeDamage(int dam);
    friend std::ostream &operator<<(std::ostream &out, const Unit &u);
    Unit &operator+=(char n);
};

class Knight : public Unit {
protected:
    explicit Knight(char pict,int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class Ranger : public Unit {
protected:
    explicit Ranger(char pict,int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class Wizard : public Unit {
protected:
    explicit Wizard(char pict,int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class Cavalry : public Knight {
public:
    Cavalry(int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class Infantry : public Knight {
public:
    Infantry(int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class Sniper : public Ranger {
public:
    Sniper(int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class Rifleman : public Ranger {
public:
    Rifleman(int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class YellowWizard : public Wizard {
public:
    YellowWizard(int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class GreenWizard : public Wizard {
public:
    GreenWizard(int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};

class Player : public Unit {
public:
    explicit Player(char digit ,int t_id = -1, int t_health = 0, int t_damage = 0, int t_armor = 0);
};


class Base : public AbstractObject {
    std::stringstream log;
    LoggerC logger;
    int maxUnitCount = 0;
    int health;
    std::vector<Unit *> units;
public:
    bool isUnitLimit();
    int getHealth() const;
    explicit Base(std::vector<Unit *> units, int maxUnit, int t_health = 0);
    int takeDamage(int dam);
    void addEnemy(Unit *u);
    void killEnemy(Unit *u);
    std::vector<Unit *> getUnits();
    void printUnitsInfo();
    void printUnitsInfo(Unit *u);
    void printBase();
    ~Base();
};

#endif //OOP_UNIT_H