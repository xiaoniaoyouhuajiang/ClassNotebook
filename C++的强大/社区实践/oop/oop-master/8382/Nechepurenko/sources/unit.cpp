#include "../headers/unit.hpp"

Unit::Unit(ObjectType c_type, std::string c_name, int16_t c_health_points, int16_t c_armor, int16_t c_attack_points) {
    this->attributes.type = c_type;
    this->attributes.name = c_name;
    this->attributes.health = c_health_points;
    this->attributes.armor = c_armor;
    this->attributes.damage = c_attack_points;
}

Unit::Unit(UnitParamList* params){
    this->attributes.type = params->type;
    this->attributes.name = params->name;
    this->attributes.health = params->health;
    this->attributes.armor = params->armor;
    this->attributes.damage = params->damage;
}

std::ostream& operator<<(std::ostream& os, const Unit& au) {
    os << au.attributes.name << "{type: " << au.attributes.type << ", hp: " << au.attributes.health;
    os << ", armor: " << au.attributes.armor << ", damage: " << au.attributes.damage << "}";
    return os; 
}

Unit::Unit(const Unit & au) { //copy constructor
    this->attributes = au.attributes; 
}

Unit& Unit::operator=(const Unit & au) {
    if (this == &au)
        return *this;
    
    this->attributes = au.attributes;

    return *this;
}

Unit::Unit(Unit&& au) {
    this->attributes = au.attributes;
}

Unit& Unit::operator=(Unit&& au) {
    if (this == &au)
        return *this;
    
    this->attributes = au.attributes;

    return *this;
}

// Unit::~Unit() {}

ObjectType Unit::getType() const noexcept {
    return this->attributes.type;
}

std::string Unit::getName() const noexcept {
    return this->attributes.name;
}

int16_t Unit::getHealth() const noexcept {
    return this->attributes.health;
}

int16_t Unit::getArmor() const noexcept {
    return this->attributes.armor;
}

int16_t Unit::getDamage() const noexcept {
    return this->attributes.damage;
}

void Unit::setType(ObjectType const & c_type) {
    this->attributes.type = c_type;
}

void Unit::setName(std::string const & c_name) {
    this->attributes.name = c_name;
}

void Unit::setHealth(int16_t const & c_health_points) {
    this->attributes.health = c_health_points;
}

void Unit::setArmor(int16_t const & c_armor_points) {
    this->attributes.armor = c_armor_points;
}

void Unit::setAttack(int16_t const & c_attack_points){
    this->attributes.damage = c_attack_points;
}

void Unit::moveUp(){
    this->mover->move(this, Move::UP);
}
void Unit::moveDown(){
    this->mover->move(this, Move::DOWN);
}
void Unit::moveLeft(){
    this->mover->move(this, Move::LEFT);
}
void Unit::moveRight(){
    this->mover->move(this, Move::RIGHT);
}
void Unit::attack(uint32_t y, uint32_t x){
    this->attacker->attack(y, x, attributes.damage);
}