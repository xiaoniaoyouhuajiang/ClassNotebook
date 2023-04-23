#include "Unit.h"
#include <iostream>
#include <utility>

using std::cout;
using std::endl;
using std::cin;
using std::pair;
using std::vector;
using std::rand;

Unit::Unit(char pict) : AbstractObject(pict), id{IDGenerator::getNextID()} {}

int Unit::getHealth() const {
    return health;
}

int Unit::getID() const {
    return id;
}

int Unit::takeDamage(int dam) {
    int takedDam = (dam - (armor + rand() % 2));
    health = health - takedDam;
    return takedDam;
}

int Unit::giveDamage() const {
    return damage + rand() % 3 + 10;
}

std::ostream &operator<<(std::ostream &out, const Unit &u) {
    out << "ID:\t" << u.id << "\nName:\t" << u.pict << "\nHP:\t" << u.health << "\nDAM:\t" << u.damage << "\nARM:\t"
        << u.armor;
    return out;
}

bool Unit::getIsEnemy() const {
    return isEnemy;
}

Unit &Unit::operator+=(char n) {
    switch (n) {
        case '+':
            this->health += rand() % 10 + 10;
            break;
        case 'o':
            this->armor += 1;
            break;
        case 'X':
            this->armor += 5;
            this->damage += 5;
            break;
        case '?':
            switch (rand() % 2) {
                case 0:
                    this->takeDamage(50);
                    break;
                case 1:
                    this->damage += 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return *this;
}


int IDGenerator::s_nextID = 1;

int IDGenerator::getNextID() { return s_nextID++; }

Knight::Knight(char pict) : Unit(pict) {}

Cavalry::Cavalry() : Knight('C') {
    armor = 4 + rand() % 3 - 1;
    damage = 2 + rand() % 3 - 1;
}

Infantry::Infantry() : Knight('I') {
    armor = 2 + rand() % 3 - 1;
    damage = 4 + rand() % 3 - 1;
}


Ranger::Ranger(char pict) : Unit(pict) {}

Sniper::Sniper() : Ranger('S') {
    armor = 1 + rand() % 3 - 1;
    damage = 5 + rand() % 3 - 1;
}

Rifleman::Rifleman() : Ranger('R') {
    armor = 3 + rand() % 3 - 1;
    damage = 3 + rand() % 3 - 1;
}


Wizard::Wizard(char pict) : Unit(pict) {}

YellowWizard::YellowWizard() : Wizard('Y') {
    armor = 1 + rand() % 3 - 1;
    damage = 2 + rand() % 3 - 1;
}

GreenWizard::GreenWizard() : Wizard('G') {
    armor = 3 + rand() % 3 - 1;
    damage = 2 + rand() % 3 - 1;
}


Player::Player(char digit) : Unit(digit) {
    id = 0;
    armor = 6;
    damage = 6;
    health = 100;
    isEnemy = false;
}

Base::Base(vector<Unit *> units, int unitCount, int maxUnit)
        : AbstractObject('$'), health(555), units(std::move(units)),
          unitCount(unitCount), maxUnitCount(maxUnit) {}

int Base::takeDamage(int dam) {
    log.str("");
    log <<"Base: Player fight with Base! (HP: " << health << ")" << endl;
    logger << log.str();
    cout << "You fight with EnemyBase! (HP: " << health << ")" << endl;
    int takedDam = (dam - (10 + rand() % 2));
    health = health - takedDam;
    return takedDam;
}

int Base::getHealth() const {
    return health;
}

void Base::addEnemy(Unit *u) {
    if (isUnitLimit()){
        logger << "Base: So many units!";
        return;
    }
    auto it = std::find(units.begin(), units.end(), u);
    if (it == units.end()) {
        units.push_back(u);
        unitCount++;
    }
}

void Base::printUnitsInfo() {
    for (auto u:units) {
        cout << *u << endl << endl;
    }
}

void Base::printUnitsInfo(Unit *u) {
    cout << *u << endl;
}

void Base::killEnemy(Unit *u) {
    logger << "Base: Oh no, my unit died.";
    auto it = std::find(units.begin(), units.end(), u);
    if (it != units.end()) {
        units.erase(it);
        unitCount--;
    }
}

vector<Unit *> Base::getUnits() {
    return units;
}

void Base::printBase() {
    cout << "Base HP: " << health << endl;
}

bool Base::isUnitLimit() {
    return unitCount >= maxUnitCount;
}

