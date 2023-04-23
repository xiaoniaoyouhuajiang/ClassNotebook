#include "powerup.hpp"

Powerup::Powerup() {
    amount_heal = 0;
    amount_str = 0;
    amount_dex = 0;
    amount_money = 0;
}

string Powerup::get_info() {
    string info = "POWERUP";

    if (amount_heal)
        info += "\nHealth: +" + to_string(amount_heal);
    if (amount_str)
        info += "\nStrength: +" + to_string(amount_str);
    if (amount_dex)
        info += "\nDexterity: +" + to_string(amount_dex);
    if (amount_money)
        info += "\nMoney: +" + to_string(amount_money);

    return info;
}

void Powerup::apply_to_unit(UnitInterface* unit) {
    unit->heal(amount_heal);
    unit->increase_strength(amount_str);
    unit->increase_dexterity(amount_dex);
}

void Powerup::apply_to_player(Player* player) {
    player->money += amount_money;
}

PowerupHealth::PowerupHealth() : Powerup() {
    amount_heal = 7;
}

PowerupStr::PowerupStr() : Powerup() {
    amount_str = 2;
}

PowerupDex::PowerupDex() : Powerup() {
    amount_dex = 1;
}

PowerupMoney::PowerupMoney() : Powerup() {
    amount_money = 15;
}

Powerup* Powerup::random_powerup() {
    int powerup_id = rand() % 4;

    switch (powerup_id) {
    case 0:
        return new PowerupHealth();
    case 1:
        return new PowerupStr();
    case 2:
        return new PowerupDex();
    case 3:
        return new PowerupMoney();
    }

    return nullptr;
}
