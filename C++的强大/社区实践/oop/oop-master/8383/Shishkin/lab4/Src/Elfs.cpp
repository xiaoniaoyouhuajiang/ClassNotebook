#include "Elfs.h"

Elfs::Elfs() {
	this->boost = 2;
	this->SetDamage(this->GetDamage() * boost);
	this->SetArmor(this->GetArmor() / boost);
	this->SetValue("E");
}

Elfs::~Elfs() {

}

void Elfs::SetBoost(int boost) {
	this->boost = boost;
	this->SetDamage(this->GetDamage() * boost);
	this->SetArmor(this->GetArmor() / boost);
}

//------------------------------------

Archer::Archer() : Elfs() {
	this->arr = 2;
	this->SetValue("EA");
	this->counter = 0;
}

Archer::~Archer() {

}

int Archer::GetCounter() {
	return counter;
}

void Archer::SetCounter(int counter) {
	this->counter = counter;
}

//------------------------------------

Invisible::Invisible() : Elfs() {
	this->invis = 3;
	this->SetValue("EI");
	this->counter = 0;
}

Invisible::~Invisible() {

}

int Invisible::GetCounter() {
	return counter;
}

void Invisible::SetCounter(int counter) {
	this->counter = counter;
}
