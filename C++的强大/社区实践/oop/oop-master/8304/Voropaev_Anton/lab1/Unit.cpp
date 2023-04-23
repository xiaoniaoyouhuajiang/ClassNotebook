
#include <iostream>
#include "Unit.h"
#include "Field.h"
#define DEFAULT 1

Unit::~Unit() = default;

void Unit::attack(Field *f, Unit* target) {
    if (!f){
        std::cout << "Invalid field pointer passed\n";
        return;
    }

    if (!target){
        std::cout << "Invalid target passed\n";
        return;
    }

	if (sqrt(pow(abs(this->getPosition().first - target->getPosition().first), 2)
		+ pow(abs(this->getPosition().second - target->getPosition().second), 2)) <= this->getRange())
	{
		target->actDamaged(this->getDamage());
		return;
	}

	else{
	    std::cout << "Out of attack range\n";
	    return;
	}

}


void Unit::move(Field *f, int dX, int dY) {
    if (!f){
        std::cout << "Invalid field passed\n";
        return;
    }

	if (!(f->moveUnit(this->getPosition().first, this->getPosition().second, dX, dY))){
	    std::cout << "Move failed\n";
	    return;
	}
	this->setPosition(this->getPosition().first + dX, this->getPosition().second + dY);
}




Archer::~Archer() = default;

Archer::Archer(int health, int dmg, int range, int armor) {
    if (health <= 0){
        std::cout << "Cannot create negative-health unit, health set to DEFAULT\n";
        this->setHealth(DEFAULT);
    }
    else {
        this->setHealth(health);
    }

    if (dmg <= 0){
        std::cout << "Cannot create negative-dmg unit, health set to DEFAULT\n";
        this->setDamage(DEFAULT);
    }
    else {
        this->setDamage(dmg);
    }

	this->setRange(range);
    if (range <= 0){
        std::cout << "Cannot create negative-attack-range unit, health set to DEFAULT\n";
        this->setRange(DEFAULT);
    }
    else {
        this->setRange(range);
    }

	this->setArmor(armor);
    if (armor <= 0){
        std::cout << "Cannot create negative-armor unit, health set to DEFAULT\n";
        this->setArmor(DEFAULT);
    }
    else {
        this->setArmor(armor);
    }
}



Knight::~Knight() = default;

Knight::Knight(int health, int dmg, int range, int armor) {
    if (health <= 0){
        std::cout << "Cannot create negative-health unit, health set to DEFAULT\n";
        this->setHealth(DEFAULT);
    }
    else {
        this->setHealth(health);
    }

    if (dmg <= 0){
        std::cout << "Cannot create negative-dmg unit, health set to DEFAULT\n";
        this->setDamage(DEFAULT);
    }
    else {
        this->setDamage(dmg);
    }

    this->setRange(range);
    if (range <= 0){
        std::cout << "Cannot create negative-attack-range unit, health set to DEFAULT\n";
        this->setRange(DEFAULT);
    }
    else {
        this->setRange(range);
    }

    this->setArmor(armor);
    if (armor <= 0){
        std::cout << "Cannot create negative-armor unit, health set to DEFAULT\n";
        this->setArmor(DEFAULT);
    }
    else {
        this->setArmor(armor);
    }
}



Cavalry::~Cavalry() = default;

Cavalry::Cavalry(int health, int dmg, int range, int armor) {
    if (health <= 0){
        std::cout << "Cannot create negative-health unit, health set to DEFAULT\n";
        this->setHealth(DEFAULT);
    }
    else {
        this->setHealth(health);
    }

    if (dmg <= 0){
        std::cout << "Cannot create negative-dmg unit, health set to DEFAULT\n";
        this->setDamage(DEFAULT);
    }
    else {
        this->setDamage(dmg);
    }

    this->setRange(range);
    if (range <= 0){
        std::cout << "Cannot create negative-attack-range unit, health set to DEFAULT\n";
        this->setRange(DEFAULT);
    }
    else {
        this->setRange(range);
    }

    this->setArmor(armor);
    if (armor <= 0){
        std::cout << "Cannot create negative-armor unit, health set to DEFAULT\n";
        this->setArmor(DEFAULT);
    }
    else {
        this->setArmor(armor);
    }
}




















