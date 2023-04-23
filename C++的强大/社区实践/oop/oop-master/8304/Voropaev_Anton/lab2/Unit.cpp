
#include <iostream>
#include "Unit.h"
#include "Field.h"
#define DEFAULT 1

Object::~Object() = default;
Unit::~Unit() = default;


void Unit::move(Field *f, int dX, int dY) {


    if (!f){
        std::cout << "Invalid field passed\n";
        return;
    }

	if (!(f->moveUnit(this->getPosition().first - 1, this->getPosition().second - 1, dX, dY))){
	    std::cout << "Move failed\n";
	    return;
	}
	this->setPosition(this->getPosition().first + dX, this->getPosition().second + dY);
}

void Unit::say_attributes() {
    if(this->name == 'n')
        std::cout << "Novice archer's attributes :\n";
    else if(this->name == 'm')
        std::cout << "Master archer's attributes :\n";
    else if(this->name == 's')
        std::cout << "Shieldsman's attributes :\n";
    else if(this->name == 'w')
        std::cout << "Swordsman's attributes :\n";
    else if(this->name == 'c')
        std::cout << "Cavalier's attributes :\n";
    else if(this->name == 'p')
        std::cout << "Paladin's attributes :\n";
    std::cout << "Health: " << this->getHealth() <<
              "\nArmor: " << this->getArmor() <<
              "\nDamage: " << this->getDamage() <<
              "\nAttack range: " << this->getRange() <<
              "\nPosition: (" << this->getPosition().first << ',' << this->getPosition().second << ")\n";


    std::cout << "Attributes effected by landscape: ";
    if(this->landscape_effect.effect_num != 0) {
        switch (this->landscape_effect.type) {
            case (EffectTypes::Range) :
                std::cout << "range(" << this->landscape_effect.effect_num << ")\n";
                break;
            case (EffectTypes::Damage) :
                std::cout << "damage(" << this->landscape_effect.effect_num << ")\n";
                break;
            case (EffectTypes::Health) :
                std::cout << "health(" << this->landscape_effect.effect_num << ")\n";
                break;
        }
    }
    else {
        std::cout << "none\n";
    }

}

int Unit::operator()(Unit* target) { //Attack
    if (!target){
        std::cout << "Invalid target passed\n";
        return 1;
    }

    if (sqrt(pow(abs(this->getPosition().first - target->getPosition().first), 2)
             + pow(abs(this->getPosition().second - target->getPosition().second), 2)) <= this->getRange()) {
        target->actDamaged(this->getDamage());
        return 0;
    }
    else {
        std::cout << "Out of attack range\n";
        return 1;
    }
}


Archer::~Archer() = default;

Archer::Archer(int health, int dmg, int range, int armor, char name) {
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

    this->name = name;
}



Knight::~Knight() = default;

Knight::Knight(int health, int dmg, int range, int armor, char name) {
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

    this->name = name;
}



Cavalry::~Cavalry() = default;

Cavalry::Cavalry(int health, int dmg, int range, int armor, char name) {
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

    this->name = name;
}


