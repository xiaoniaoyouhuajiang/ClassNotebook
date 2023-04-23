#pragma once


class Damage {

private:
	int damage;
public:
	Damage() {};
	int getDamage() {
		return damage;
	}
	void setDamage(int a) {
		damage = a;
	}
	void raiseDamage(int value) {
		damage = damage + value;
	}
	~Damage() {};
};

class Armor {
private:
	int armor;
public:
	Armor() {};
	int getArmor() {
		return armor;
	}
	void setArmor(int a) {
		armor = a;
	}
	void reduceHealth(int d) {
		armor = armor - d;

	}
	~Armor() {};

};

class Unit {

private:

	char id;
	Damage *damage;
	Armor *armor;
	int speed;

public:

	Unit() { id = '0'; damage = new Damage; armor = new Armor; speed = 0; };

	void SetCharacteristics(int a, int b, int c) {
		setDamage(a);
		setArmor(b);
		this->speed = c;

	}
	void attack(Unit* a) {
		a->get_hit(damage->getDamage());
	}
	void get_hit(int damage) {
		armor->reduceHealth(damage);
	}
	void check_armor(Unit* a) {
		if (a->getArmor() < 0)
			a->~Unit();
	}
	void weapon_upgrade() {
		damage->raiseDamage(5);
	}
	void setName(char a) {
		this->id = a;
	}
	char getid() {
		return id;
	}
	int getSpeed() {
		return speed;
	}
	int getDamage() {
		return damage->getDamage();;
	}
	int getArmor() {
		return armor->getArmor();
	}
	void setDamage(int a) {
		armor->setArmor(a);
	}
	void setArmor(int a) {
		damage->setDamage(a);
	} 
	void setSpeed(int a) {
		this->speed = a;
	}

	~Unit() {

	};

};

class Warrior : public Unit {

public:

	Warrior() {
		this->SetCharacteristics(10, 8, 2);
	};
	~Warrior() {};

};

class Swordman : public Warrior {

public:

	Swordman() {

		this->setName('a');
	}
	~Swordman() {};
};

class Spearman : public Warrior {

public:

	Spearman() {

		this->setName('b');

	};
	~Spearman() {};

};

class Archer : public Unit {

public:

	Archer() {
		this->SetCharacteristics(15, 5, 3);


	}
	~Archer() {};
};

class Slinger : public Archer {

public:

	Slinger() {

		this->setName('c');

	};
	~Slinger() {};

};

class Bowman : public Archer {

public:

	Bowman() {

		this->setName('d');


	};
	~Bowman() {};
};

class Cavalry : public Unit {

public:

	Cavalry() {

		this->SetCharacteristics(15, 10, 5);

	};
	~Cavalry() {};

};

class LightCavalry : public Cavalry {

public:

	LightCavalry() {

		this->setName('e');

	};
	~LightCavalry() {};


};

class HeavyCavalry : public Cavalry {

public:

	HeavyCavalry() {

		this->setName('f');

	};
	~HeavyCavalry() {};

};

