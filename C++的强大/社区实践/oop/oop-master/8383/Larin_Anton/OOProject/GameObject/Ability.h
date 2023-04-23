//
// Created by anton on 5/9/20.
//

#ifndef OOPROJECT_ABILITY_H
#define OOPROJECT_ABILITY_H


//#include "GameObject.h"
class GameObject;

struct Ability {
    int power;
    int range;
    GameObject* master;

    Ability(int power, int range, GameObject *master);
};


#endif //OOPROJECT_ABILITY_H
