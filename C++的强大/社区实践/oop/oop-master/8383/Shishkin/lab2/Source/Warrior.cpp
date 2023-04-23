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
	this->abilityToWalk = 0;
}

Warrior::~Warrior() {
	this->placex = -1;
	this->placey = -1;
	this->health = 0;
	this->damage = 0;
	this->armor = 0;
	this->value = "---";
	this->abilityToWalk = 0;
}

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

void Warrior::SetAbilityToWalk(int atw) {
	this->abilityToWalk = atw;
}

int Warrior::GetAbilityToWalk() {
	return abilityToWalk;
}

void Warrior::attack(Warrior& w2) {
	w2.SetHealth(w2.GetHealth() - damage);

	if (w2.GetHealth() <= 0) {
		w2.SetValue("---");
		//w2.~Warrior();
	}
}
