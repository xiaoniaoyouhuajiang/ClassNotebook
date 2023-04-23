#include "Attribute.h"

void Attribute::newSetValue(int newValue) {
	this->value = newValue;
}

int Attribute::getValue() {
	return value;
}

Damage::Damage() {
	this->value = 0;
}

Armor::Armor() {
	this->value = 0;
}

Health::Health() {
	this->value = 0;
}