#pragma once

#include "../Player/player.hpp"
#include "neutral.hpp"

class Powerup : public NeutralInterface {
public:
    unsigned amount_heal;
    unsigned amount_str;
    unsigned amount_dex;
    unsigned amount_money;

    Powerup();
    virtual NeutralInterface* create_copy() = 0;

    string get_info() override;
    void apply_to_unit(UnitInterface* unit) override;
    void apply_to_player(Player* player) override;

    static Powerup* random_powerup();
};

class PowerupHealth : public Powerup {
public:
    PowerupHealth();
    NeutralInterface* create_copy() { return new PowerupHealth(); }
};

class PowerupStr : public Powerup {
public:
    PowerupStr();
    NeutralInterface* create_copy() { return new PowerupStr(); }
};

class PowerupDex : public Powerup {
public:
    PowerupDex();
    NeutralInterface* create_copy() { return new PowerupDex(); }
};

class PowerupMoney : public Powerup {
public:
    PowerupMoney();
    NeutralInterface* create_copy() { return new PowerupMoney(); }
};
