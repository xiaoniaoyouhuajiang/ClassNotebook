#pragma once

#include <cmath>
#include <utility>
#include <memory>

class Field;

class Location {
public:
	Location(int x, int y) {
		this->position.first = x;
		this->position.second = y;
	}

	explicit Location(std::pair<int, int> pos) {
		this->position = pos;
	}

	Location() = default;
	~Location() = default;

	void setPosition(int x, int y) {
		this->position.first = x;
		this->position.second = y;
	}

	void setPosition(std::pair<int, int> pos) {
		this->position = pos;
	}

	std::pair<int, int> getPosition() const {
		return position;
	}

private:
	std::pair<int, int> position;


};


class Health
{
public:
	Health() {
		health = 0;
	}
	~Health() = default;

	explicit Health(int h) {
		this->health = h;
	}

	int getHealth() {
		return health;

	}

	void setHealth(int h) {
		this->health = h;
	}

	void actDamaged(int dmg) {

		this->health -= dmg;
	}

	void actHealed(int heal) {
		this->health += heal;
	}

private:
	int health;

};


class Damage
{
public:
	Damage() {
		damage = 0;
		range = 0;
	}
	~Damage() = default;

	Damage(int d, int r) {
		this->damage = d;
		this->range = r;
	}

	int getDamage() const {
		return damage;

	}

	void setDamage(int d) {
		damage = d;
	}

	int getRange() const {
		return range;

	}

	void setRange(int r) {
		range = r;
	}

	void actDecreaseDmg(int debuff) {

		damage -= debuff;
	}

	void actIncreaseDmg(int buff) {
		damage += buff;
	}

private:
	int damage;
	int range;

};


class Armor
{
public:

	Armor() {
		armor = 0;
	}
	~Armor() = default;

	explicit Armor(int a) {
		this->armor = a;
	}

	int getArmor() const {
		return armor;

	}

	void setArmor(int a) {
		armor = a;
	}

	void actDecreaseArmor(int debuff) {

		armor -= debuff;
	}

	void actIncreaseArmor(int buff) {
		armor += buff;
	}

private:
	int armor;

};


class Unit :public Armor, public Health, public Damage, public Location {
public:
	Unit() = default;

	virtual Unit* clone() = 0;

	virtual ~Unit() = 0;

    void move(Field *f, int dX, int dY);

    void attack(Field *f, Unit* target);
};


class Archer : public Unit {
public:
	Archer() = default;

	explicit Archer(int health, int dmg, int range, int armor);

	~Archer() override = 0;

};


class MasterArcher : public Archer {
public:
	MasterArcher() : Archer(500, 50, 10, 15)
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
	NoviceArcher() : Archer(300, 30, 10, 8)
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

	explicit Knight(int health, int dmg, int range, int armor);

	~Knight() override = 0;

};



class Swordsman : public Knight {

public:
	Swordsman() : Knight(900, 75, 5, 20)
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
	Shieldman() : Knight(1400, 40, 2, 35)
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

	explicit Cavalry(int health, int dmg, int range, int armor);

	~Cavalry() override = 0;
};



class Paladin : public Cavalry {

public:
	Paladin() : Cavalry(800, 60, 8, 20)
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
    Cavalier() : Cavalry(600, 55, 8, 20)
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





















