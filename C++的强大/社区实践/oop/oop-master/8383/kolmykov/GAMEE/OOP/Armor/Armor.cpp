#include "Armor.h"



Armor::Armor()
{
}

Armor::Armor(const Armor & other) {
	this->defend = other.defend;
}


Armor::~Armor() {

}


int Armor::getDefend() {
	return defend;
}