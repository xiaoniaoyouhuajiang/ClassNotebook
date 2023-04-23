#include "units.hpp"
#include "../Player/player.hpp"

using namespace std;

void Unit::heal(unsigned amount) {
    health.increase(amount);
}

void Unit::damage(unsigned amount) {
    health.decrease(amount);
}

void Unit::reset_status() {
    moved = false;
    attacked = false;
}

void Unit::notify_about_death() {
    if (owner) {
        owner->react_unit_death(this);
    }
}

UnitInterface* Unit::create_unit(UnitType type) {
    switch (type) {
    case UnitType::WARRIOR:   return new UnitWarrior();
    case UnitType::KNIGHT:    return new UnitKnight();
    case UnitType::ARCHER:    return new UnitArcher();
    case UnitType::ARBALET:   return new UnitArbalet();
    case UnitType::MAGEFIRE:  return new UnitMageFire();
    case UnitType::MAGEFROST: return new UnitMageFrost();
    }
    return nullptr;
}

string Unit::get_info() {
    string info;

    info += get_name() + "\n";
    info += "Health: " + to_string(health.get_value()) + "/" +
            to_string(health.get_max_value()) + "\n";
    info += "Range: " + to_string(attack_range) + "\n";
    info += "Strength: " + to_string(strength.get_value()) + "\n";
    info += "Dexterity: " + to_string(dexterity.get_value());

    return info;
}

UnitConstStats* UnitWarrior::const_stats = new UnitConstStats(30, 1);

UnitWarrior::UnitWarrior() {
    health = Attribute(const_stats->health_max, const_stats->health_max);
    attack_range = const_stats->attack_range;
    strength = Attribute(9, 1000);
    dexterity = Attribute(4, 1000);
}

UnitConstStats* UnitKnight::const_stats = new UnitConstStats(40, 1);

UnitKnight::UnitKnight() {
    health = Attribute(const_stats->health_max, const_stats->health_max);
    attack_range = const_stats->attack_range;
    strength = Attribute(7, 1000);
    dexterity = Attribute(3, 1000);
}

UnitConstStats* UnitArcher::const_stats = new UnitConstStats(22, 5);

UnitArcher::UnitArcher() {
    health = Attribute(const_stats->health_max, const_stats->health_max);
    attack_range = const_stats->attack_range;
    strength = Attribute(6, 1000);
    dexterity = Attribute(5, 1000);
}

UnitConstStats* UnitArbalet::const_stats = new UnitConstStats(16, 4);

UnitArbalet::UnitArbalet() {
    health = Attribute(const_stats->health_max, const_stats->health_max);
    attack_range = const_stats->attack_range;
    strength = Attribute(7, 1000);
    dexterity = Attribute(6, 1000);
}

UnitConstStats* UnitMageFrost::const_stats = new UnitConstStats(20, 5);

UnitMageFrost::UnitMageFrost() {
    health = Attribute(const_stats->health_max, const_stats->health_max);
    attack_range = const_stats->attack_range;
    strength = Attribute(6, 1000);
    dexterity = Attribute(5, 1000);
}

UnitConstStats* UnitMageFire::const_stats = new UnitConstStats(18, 5);

UnitMageFire::UnitMageFire() {
    health = Attribute(const_stats->health_max, const_stats->health_max);
    attack_range = const_stats->attack_range;
    strength = Attribute(6, 1000);
    dexterity = Attribute(6, 1000);
}

UnitInterface* random_unit() {
    return new UnitWarrior();
}
