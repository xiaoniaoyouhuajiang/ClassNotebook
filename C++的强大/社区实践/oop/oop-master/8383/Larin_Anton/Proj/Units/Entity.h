//
// Created by anton on 2/25/20.
//

#ifndef PROJ_ENTITY_H
#define PROJ_ENTITY_H


#include "../GameObject.h"


class Entity : public GameObject {
    Entity &operator+=(const GameObject &other);
};


#endif //PROJ_ENTITY_H
