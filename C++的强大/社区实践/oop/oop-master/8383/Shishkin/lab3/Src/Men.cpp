#include "Men.h"

Men::Men() {
	this->boost = 2;
	this->SetHealth(this->GetHealth() / boost);
	this->SetDamage(this->GetDamage() * boost);
	this->SetArmor(this->GetArmor() * boost);
	this->SetValue("M");
}

Men::~Men() {

}

void Men::SetBoost(int boost) {
	this->boost = boost;
	this->SetHealth(this->GetHealth() / boost);
	this->SetDamage(this->GetDamage() * boost);
	this->SetArmor(this->GetArmor() * boost);
}

//------------------------------------

Spearman::Spearman() : Men() {
	this->barbecue = 1;
	this->SetValue("MS");
	this->counter = 0;
}

Spearman::~Spearman() {

}

int Spearman::GetCounter() {
	return counter;
}

void Spearman::SetCounter(int counter) {
	this->counter = counter;
}

//------------------------------------

Wizard::Wizard() : Men() {
	this->range = 1;
	this->SetDamage(this->GetDamage() / 3);
	this->SetValue("MW");
	this->counter = 0;
}

Wizard::~Wizard() {

}

int Wizard::GetCounter() {
	return counter;
}

void Wizard::SetCounter(int counter) {
	this->counter = counter;
}
