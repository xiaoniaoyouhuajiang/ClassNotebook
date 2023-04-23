#include "player.hpp"

Player::Player(unsigned id) {
    this->id = id;
    this->money = 100;
    this->max_units = PLAYER_MAX_UNITS;
    this->base = NULL;
}

Player::~Player() {
}

string Player::get_info() {
    string info;

    info += string("Player: ") + to_string(id) + "\n";
    info += "Money: " + to_string(money) + "\n";
    info += string("Units: ") + to_string(units.size()) + "/" +
            to_string(max_units);

    return info;
}

Base* Player::create_base(Coordinates coors) {
    base = new Base(id, coors);
    return base;
}

void Player::set_base(Base* base) {
    this->base = base;
}

void Player::add_unit(UnitInterface* unit) {
    units.push_back(unit);
}

void Player::react_unit_death(UnitInterface* unit) {
    units.erase(find(units.begin(), units.end(), unit));
}
