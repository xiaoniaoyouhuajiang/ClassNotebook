#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include "object.hpp"
#include "map.hpp"

class Attackable {
    public:
        virtual void attack(uint32_t y, uint32_t x, uint32_t damage) = 0;
        void perform(uint32_t y, uint32_t x, uint32_t damage);


};

class MeleeAttack : public Attackable {
    public:
        void attack(uint32_t y, uint32_t x, uint32_t damage);
};

class RangeAttack : public Attackable {
    public:
        void attack(uint32_t y, uint32_t x, uint32_t damage);
    private:
        uint32_t range = 10;
};

class DefaultAttributes {
    public:
        std::string name = "Default_name";
        ObjectType type = ObjectType::EMPTY;

};

class UnitAttributes : public DefaultAttributes {
    public:
        UnitAttributes(int16_t health = 100, int16_t armor = 10, int16_t damage = 30)
        : health(health), armor(armor), damage(damage) {} 
        int16_t health;
        int16_t armor;
        int16_t damage;
};


class Moveable {
    public:
        virtual void move(Object* ao, Move direction) = 0;
        std::shared_ptr<MapCell> ableMove(uint32_t y, uint32_t x);


};

class SimpleMove : public Moveable {
    public:
        void move(Object* ao, Move direction);
        
};

class UnitParamList : public UnitAttributes {
    public:
        UnitParamList(ObjectType type, std::string name = "Unknown", int16_t health = 100, int16_t armor = 10, int16_t damage = 30)
        : UnitAttributes(health, armor, damage), type(type), name(name) {}
        ObjectType type;
        std::string name;
};