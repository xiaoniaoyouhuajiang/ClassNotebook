#pragma once

#include "../../Logging/logger_proxy.hpp"
#include "attribute.hpp"
#include "concrete_unit_factory.hpp"
#include <string>

#define UNIT_COST 10

class Player;

using namespace std;

enum UnitType { WARRIOR, KNIGHT, ARCHER, ARBALET, MAGEFROST, MAGEFIRE };

class UnitConstStats {
public:
    unsigned health_max;
    unsigned attack_range;
    UnitConstStats(unsigned health_max, unsigned attack_range)
        : health_max(health_max), attack_range(attack_range) {}
};

class UnitInterface {
public:
    virtual ~UnitInterface() = default;
    virtual UnitInterface* create_copy() = 0;

    virtual void heal(unsigned amount) = 0;
    virtual void damage(unsigned amount) = 0;
    virtual void increase_strength(unsigned amount) = 0;
    virtual void increase_dexterity(unsigned amount) = 0;
    virtual string get_info() = 0;
    virtual string get_name() const = 0;
    virtual UnitType get_type() const = 0;
    virtual void reset_status() = 0;

    virtual Player* get_owner() = 0;
    virtual void set_owner(Player* owner) = 0;
    virtual unsigned get_owner_id() = 0;
    virtual void set_owner_id(unsigned id) = 0;
    virtual unsigned get_health() = 0;
    virtual bool get_moved() = 0;
    virtual void set_moved(bool moved) = 0;
    virtual void set_attacked(bool attacked) = 0;
    virtual bool get_attacked() = 0;
    virtual unsigned get_dexterity() = 0;
    virtual unsigned get_strength() = 0;
    virtual unsigned get_range() = 0;

    virtual UnitFactory* create_unit_factory() = 0;
    virtual void notify_about_death() = 0;

    friend LoggerProxy& operator<<(LoggerProxy& logger,
                                   const UnitInterface& unit) {
        logger << unit.get_name();
        return logger;
    };
};

class Unit : public UnitInterface {
protected:
    unsigned owner_id;
    Player* owner = nullptr;

    Attribute health;
    // Attribute health_max;
    Attribute strength;
    unsigned attack_range;
    Attribute dexterity;

    bool moved;
    bool attacked;

public:
    ~Unit() = default;
    virtual UnitInterface* create_copy() = 0;

    void heal(unsigned amount);
    void damage(unsigned amount);
    void increase_strength(unsigned amount) { strength.increase(amount); };
    void increase_dexterity(unsigned amount) { dexterity.increase(amount); };

    string get_info();
    virtual string get_name() const = 0;

    void reset_status();

    Player* get_owner() { return owner; };
    void set_owner(Player* owner) { this->owner = owner; };
    unsigned get_health() { return health.get_value(); };
    unsigned get_owner_id() { return owner_id; };
    void set_owner_id(unsigned id) { owner_id = id; };
    void set_moved(bool moved) { this->moved = moved; };
    bool get_moved() { return moved; };
    void set_attacked(bool attacked) { this->attacked = attacked; };
    bool get_attacked() { return attacked; };
    unsigned get_dexterity() { return dexterity.get_value(); };
    unsigned get_strength() { return strength.get_value(); };

    virtual UnitFactory* create_unit_factory() = 0;
    void notify_about_death();

    static UnitInterface* create_unit(UnitType type);
};

class UnitWarrior : public Unit {
protected:
    static UnitConstStats* const_stats;

public:
    UnitWarrior();
    UnitInterface* create_copy() { return new UnitWarrior; };
    string get_name() const { return "WARRIOR"; };
    UnitType get_type() const { return UnitType::WARRIOR; };
    unsigned get_range() { return const_stats->attack_range; };
    UnitFactory* create_unit_factory() override {
        return new ConcreteUnitFactory<UnitWarrior>();
    };
};

class UnitKnight : public Unit {
protected:
    static UnitConstStats* const_stats;

public:
    UnitKnight();
    UnitInterface* create_copy() { return new UnitKnight; };
    string get_name() const { return "KNIGHT"; };
    UnitType get_type() const { return UnitType::KNIGHT; };
    unsigned get_range() { return const_stats->attack_range; };
    UnitFactory* create_unit_factory() {
        return new ConcreteUnitFactory<UnitKnight>();
    };
};

class UnitArcher : public Unit {
protected:
    static UnitConstStats* const_stats;

public:
    UnitArcher();
    UnitInterface* create_copy() { return new UnitArcher; };
    string get_name() const { return "ARCHER"; };
    UnitType get_type() const { return UnitType::ARCHER; };
    unsigned get_range() { return const_stats->attack_range; };
    UnitFactory* create_unit_factory() {
        return new ConcreteUnitFactory<UnitArcher>();
    };
};

class UnitArbalet : public Unit {
protected:
    static UnitConstStats* const_stats;

public:
    UnitArbalet();
    UnitInterface* create_copy() { return new UnitArbalet; };
    string get_name() const { return "ARBALET"; };
    UnitType get_type() const { return UnitType::ARBALET; };
    unsigned get_range() { return const_stats->attack_range; };
    UnitFactory* create_unit_factory() {
        return new ConcreteUnitFactory<UnitArbalet>();
    };
};

class UnitMageFrost : public Unit {
protected:
    static UnitConstStats* const_stats;

public:
    UnitMageFrost();
    UnitInterface* create_copy() { return new UnitMageFrost; };
    string get_name() const { return "FROST MAGE"; };
    UnitType get_type() const { return UnitType::MAGEFROST; };
    unsigned get_range() { return const_stats->attack_range; };
    UnitFactory* create_unit_factory() {
        return new ConcreteUnitFactory<UnitMageFrost>();
    };
};

class UnitMageFire : public Unit {
protected:
    static UnitConstStats* const_stats;

public:
    UnitMageFire();
    UnitInterface* create_copy() { return new UnitMageFire; };
    string get_name() const { return "FIRE MAGE"; };
    UnitType get_type() const { return UnitType::MAGEFIRE; };
    unsigned get_range() { return const_stats->attack_range; };

    UnitFactory* create_unit_factory() {
        return new ConcreteUnitFactory<UnitMageFire>();
    };
};

UnitInterface* random_unit();
