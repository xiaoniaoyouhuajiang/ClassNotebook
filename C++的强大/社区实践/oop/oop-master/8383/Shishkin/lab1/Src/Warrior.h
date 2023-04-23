#pragma once

#include <iostream>

enum Warrior_ID { Archer_ID = 0, Invisible_ID, Spearman_ID, Wizard_ID, Devourers_ID, Robbers_ID };

class Warrior {
public:
	Warrior();
	~Warrior();
	static Warrior createWarrior(Warrior_ID id); //фабричный метод
	void SetPlaceX(int placex);
	int GetPlaceX(void);
	void SetPlaceY(int placey);
	int GetPlaceY(void);
	void SetValue(std::string value);
	std::string GetValue(void);
	void SetHealth(int health);
	int GetHealth();
	void SetDamage(int damage);
	int GetDamage();
	void SetArmor(int armor);
	int GetArmor();

private:
	int placex;
	int placey;
	std::string value;

	/*Health health;
	Damage damage;
	Armor armor;*/
	int health;
	int damage;
	int armor;
};


/*class Health : public Warrior {
public:
	int GetHealth();
	void SetHealth(int health);

private:
	int health;
};

class Damage : public Warrior {
public:
	int GetDamage();
	void SetDamage(int damage);

private:
	int damage;
};

class Armor : public Warrior {
public:
	int GetArmor();
	void SetArmor(int armor);

private:
	int armor;
};*/
