//
// Created by anton on 3/19/20.
//

#ifndef PROJ_UNITPROPS_H
#define PROJ_UNITPROPS_H
enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum class UnitClass {
    ALPHA,
    BETA,
    GAMMA,
    DELTA,
    EPSILON,
    ZETA,
    BUSH,
    FIRE,
    STONE,
    TREE,
    NO_CLASS
};


enum class UnitType {
    GOD,
    MAGE,
    FIGHTER,
    NO_TYPE
};

enum class UnitDevotion {
    LIGHT,
    DARK,
    NEUTER
};
#endif //PROJ_UNITPROPS_H
