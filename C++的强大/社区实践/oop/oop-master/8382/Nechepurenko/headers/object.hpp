#pragma once
#include <cstdint>
#include <string>

enum ObjectType {EMPTY, MAIN_HERO, \
                 ENEMY_1, ENEMY_2, ENEMY_3, NEUTRAL_HEAL, NEUTRAL_ARMOR, \
                 NEUTRAL_DAMAGE, NEUTRAL_SPEED, WITCH, KNIGHT, ARCHER, BOGATYR, TAMPLIER, CHRISTIANWITCH, \
                 BURNEDWITCH, MULTIARCHER, WINDARCHER, RADIANTBASE, DIREBASE};


class Object{
    public:
        virtual ~Object() = default;
        virtual std::string repr() {return "J";};
    protected:
        Object(ObjectType c_type = ObjectType::EMPTY) {};
        ObjectType c_type;

};