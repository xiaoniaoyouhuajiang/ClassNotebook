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
    Unit(char pict);
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
    explicit Knight(char pict);
};

class Ranger : public Unit {
protected:
    explicit Ranger(char pict);
};

class Wizard : public Unit {
protected:
    explicit Wizard(char pict);
};

class Cavalry : public Knight {
public:
    Cavalry();
};

class Infantry : public Knight {
public:
    Infantry();
};

class Sniper : public Ranger {
public:
    Sniper();
};

class Rifleman : public Ranger {
public:
    Rifleman();
};

class YellowWizard : public Wizard {
public:
    YellowWizard();
};

class GreenWizard : public Wizard {
public:
    GreenWizard();
};

class Player : public Unit {
public:
    explicit Player(char digit);
};


class Base : public AbstractObject {
    std::stringstream log;
    LoggerC logger;
    int unitCount = 0;
    int maxUnitCount = 0;
    int health;
    std::vector<Unit *> units;
public:
    bool isUnitLimit();
    int getHealth() const;
    explicit Base(std::vector<Unit *> units, int unitCount, int maxUnit);
    int takeDamage(int dam);
    void addEnemy(Unit *u);
    void killEnemy(Unit *u);
    std::vector<Unit *> getUnits();
    void printUnitsInfo();
    void printUnitsInfo(Unit *u);
    void printBase();
};

#endif //OOP_UNIT_H