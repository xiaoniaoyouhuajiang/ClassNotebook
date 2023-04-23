#pragma once
#include <string>
#include <iostream>
#include "object.hpp"
#include "stuff.hpp"
enum MoveAbility {ABLE, UNABLE};

class Move4Interface {
    virtual void moveUp() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void moveDown() = 0;
};

class Unit : public Object, Move4Interface {
    friend class HealBuff;
    friend class DamageBuff;
    friend class ArmorBuff;
    friend class SpeedBuff;
    protected:
        Unit(ObjectType c_type = ObjectType::KNIGHT,
                     std::string c_name = "Unknown",
                     int16_t c_health_points = 100,
                     int16_t c_armor = 30,
                     int16_t c_attack_points = 30
                    );
        Unit(const Unit & au);
        Unit& operator=(const Unit & au);
        Unit(Unit&& au);
        Unit& operator=(Unit&& au);
        Unit(UnitParamList* params);
    public:
        virtual ~Unit() = default; // to avoid unique ptr warnings
        ObjectType getType() const noexcept;
        std::string getName() const noexcept;
        int16_t getHealth() const noexcept;
        int16_t getArmor() const noexcept;
        int16_t getDamage() const noexcept;
        void setType(ObjectType const & c_type);
        void setName(std::string const & c_name);
        void setHealth(int16_t const & c_health_points);
        void setArmor(int16_t const & c_armor_points);
        void setAttack(int16_t const & c_attack_points);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void attack(uint32_t y, uint32_t x);
        friend std::ostream& operator<<(std::ostream& os, const Unit& au);
    protected:
        UnitAttributes attributes;
        Moveable* mover = new SimpleMove();
        Attackable* attacker = new MeleeAttack();
        
};


class Knight : public Unit {
    public:
    protected:
        Knight(UnitParamList* p) : Unit(p) {
            attacker = new MeleeAttack();
        }
        ~Knight() {delete attacker;}
};

class Witch : public Unit {
    public:
    protected:
        Witch(UnitParamList* p) : Unit(p) {
            attacker = new RangeAttack();
        }
        ~Witch() {delete attacker;}
};

class Archer : public Unit {
    protected:
        Archer(UnitParamList* p) : Unit(p) {
            attacker = new RangeAttack();
        }
        ~Archer() {delete attacker;}
};

class Bogatyr : public Knight {
    public:
        Bogatyr(UnitParamList* p) : Knight(p) {
            this->attributes.type = ObjectType::BOGATYR;
        }
        ~Bogatyr() {}
        std::string repr(){
            return std::string("B");
        }
};

class Tamplier : public Knight {
    public:
        Tamplier(UnitParamList* p) : Knight (p) {
            this->attributes.type = ObjectType::TAMPLIER;
        }
        ~Tamplier() {}
        std::string repr(){
            return std::string("X");
        }
};

class ChristianWitch : public Witch {
    public:
        ChristianWitch(UnitParamList* p) : Witch(p) {
            this->attributes.type = ObjectType::CHRISTIANWITCH;
        }
        ~ChristianWitch() {}
        std::string repr(){
            return std::string("C");
        }
};

class BurnedWitch : public Witch {
    public:
        BurnedWitch(UnitParamList* p) : Witch(p) {
            this->attributes.type = ObjectType::BURNEDWITCH;
        }
        ~BurnedWitch() {}
        std::string repr(){
            return std::string("B");
        }
};

class MultiArcher : public Archer {
    public:
        MultiArcher(UnitParamList* p) : Archer(p) {
            this->attributes.type = ObjectType::MULTIARCHER;
        }
        ~MultiArcher() {}
        std::string repr(){
            return std::string("M");
        }
};

class WindArcher : public Archer {
    public:
        WindArcher(UnitParamList* p) : Archer(p) {
            this->attributes.type = ObjectType::WINDARCHER;
        }
        ~WindArcher() {}
        std::string repr(){
            return std::string("W");
        }
};