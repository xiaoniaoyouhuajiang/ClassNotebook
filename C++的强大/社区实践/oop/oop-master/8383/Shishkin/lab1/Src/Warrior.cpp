#include "Warrior.h"
#include "Elfs.h"
#include "Men.h"
#include "Orcs.h"


Warrior::Warrior() {
	this->placex = 0;
	this->placey = 0;
	this->health = 50;
	this->damage = 5;
	this->armor = 25;
	this->value = "---";
}

Warrior::~Warrior() {

}

Warrior Warrior::createWarrior(Warrior_ID id) {
	Warrior p;

	switch (id) {
	case Archer_ID:
		p = Archer();
		break;

	case Invisible_ID:
		p = Invisible();
		break;

	case Spearman_ID:
		p = Spearman();
		break;

	case Wizard_ID:
		p = Wizard();
		break;

	case Devourers_ID:
		p = Devourers();
		break;

	case Robbers_ID:
		p = Robbers();
		break;

	default:
		std::cout << "Îøèáêà\n";
	}
	return p;
};

void Warrior::SetPlaceX(int placex) {
	this->placex = placex;
}

int Warrior::GetPlaceX(void) {
	return placex;
}

void Warrior::SetPlaceY(int placey) {
	this->placey = placey;
}

int Warrior::GetPlaceY(void) {
	return placey;
}

void Warrior::SetValue(std::string value) {
	this->value = value;
}

std::string Warrior::GetValue(void) {
	return value;
}

/*void Health::SetHealth(int health) {
	this->health = health;
}

int Health::GetHealth() {
	return health;
}

void Damage::SetDamage(int damage) {
	this->damage = damage;
}

int Damage::GetDamage() {
	return damage;
}

void Armor::SetArmor(int armor) {
	this->armor = armor;
}

int Armor::GetArmor() {
	return armor;
}*/

void Warrior::SetHealth(int health) {
	this->health = health;
}

int Warrior::GetHealth() {
	return health;
}

void Warrior::SetDamage(int damage) {
	this->damage = damage;
}

int Warrior::GetDamage() {
	return damage;
}

void Warrior::SetArmor(int armor) {
	this->armor = armor;
}

int Warrior::GetArmor() {
	return armor;
}
