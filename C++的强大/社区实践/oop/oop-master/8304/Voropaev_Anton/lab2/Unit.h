#pragma once

#include <cmath>
#include <utility>
#include <memory>
#include "Unit Attributes/Location.h"
#include "Unit Attributes/Health.h"
#include "Unit Attributes/Damage.h"
#include "Unit Attributes/Armor.h"
#include "Object.h"
#include "Landscapes/Landscape.h"

class Field;

class Unit : public Object {
public:
	Unit() = default;

	~Unit() override = 0;

    void move(Field *f, int dX, int dY);

    int operator()(Unit *target); //Attack

    void say_attributes();

    LandscapeInfo landscape_effect;

    char name = 0;


};


class Archer : public Unit {
public:
	Archer() = default;

	explicit Archer(int health, int dmg, int range, int armor, char name);

	~Archer() override = 0;

};


class MasterArcher : public Archer {
public:
	MasterArcher() : Archer(500, 50, 10, 15, 'm')
	{};

	Unit* clone() final{
	    auto tmp = new MasterArcher;

	    tmp->setHealth(this->getHealth());

        tmp->setDamage(this->getDamage());

        tmp->setRange(this->getRange());

        tmp->setArmor(this->getArmor());

        return (Unit*) tmp;

	}

	~MasterArcher() final = default;
};


class NoviceArcher : public Archer {

public:
	NoviceArcher() : Archer(300, 600, 10, 8, 'n')
	{};

    Unit* clone() final{
        auto tmp = new NoviceArcher;

        tmp->setHealth(this->getHealth());

        tmp->setDamage(this->getDamage());

        tmp->setRange(this->getRange());

        tmp->setArmor(this->getArmor());

        return (Unit*) tmp;

    }

	~NoviceArcher() final = default;
};


class Knight : public Unit {

public:

	Knight() = default;

	explicit Knight(int health, int dmg, int range, int armor, char name);

	~Knight() override = 0;

};



class Swordsman : public Knight {

public:
	Swordsman() : Knight(900, 75, 5, 20, 'w')
	{};

    Unit* clone() final{
        auto tmp_for_clone = new Swordsman;

        tmp_for_clone->setHealth(this->getHealth());

        tmp_for_clone->setDamage(this->getDamage());

        tmp_for_clone->setRange(this->getRange());

        tmp_for_clone->setArmor(this->getArmor());

        return (Unit*) tmp_for_clone;

    }

	~Swordsman() final = default;

};


class Shieldman : public Knight {

public:
	Shieldman() : Knight(1400, 40, 2, 35, 's')
	{};

    Unit* clone() final{
        auto tmp_for_clone = new Shieldman;

        tmp_for_clone->setHealth(this->getHealth());

        tmp_for_clone->setDamage(this->getDamage());

        tmp_for_clone->setRange(this->getRange());

        tmp_for_clone->setArmor(this->getArmor());

        return (Unit*) tmp_for_clone;

    }

	~Shieldman() final = default;

};



class Cavalry : public Unit {

public:

	Cavalry() = default;

	explicit Cavalry(int health, int dmg, int range, int armor, char name);

	~Cavalry() override = 0;
};



class Paladin : public Cavalry {

public:
	Paladin() : Cavalry(800, 60, 8, 20, 'p')
	{};

    Unit* clone() final{
        auto tmp_for_clone = new Paladin;

        tmp_for_clone->setHealth(this->getHealth());

        tmp_for_clone->setDamage(this->getDamage());

        tmp_for_clone->setRange(this->getRange());

        tmp_for_clone->setArmor(this->getArmor());

        return (Unit*) tmp_for_clone;

    }

	~Paladin() final = default;

};


class Cavalier : public Cavalry {

public:
    Cavalier() : Cavalry(600, 55, 8, 20, 'c')
    {};

    Unit* clone() final{
        auto tmp = new Cavalier;

        tmp->setHealth(this->getHealth());

        tmp->setDamage(this->getDamage());

        tmp->setRange(this->getRange());

        tmp->setArmor(this->getArmor());

        return (Unit*) tmp;

    }

	~Cavalier() final = default;

};





















