//
// Created by anton on 5/9/20.
//

#ifndef OOPROJECT_MOBILITY_H
#define OOPROJECT_MOBILITY_H


//#include "GameObject.h"
class GameObject;

struct Mobility {
    Mobility(int agility, int range, GameObject *master);

    int agility;
    int range;
    GameObject* master;
};


#endif //OOPROJECT_MOBILITY_H
