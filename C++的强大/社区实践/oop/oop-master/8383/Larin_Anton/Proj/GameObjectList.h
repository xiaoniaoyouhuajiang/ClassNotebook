//
// Created by anton on 3/2/20.
//

#ifndef PROJ_GAMEOBJECTLIST_H
#define PROJ_GAMEOBJECTLIST_H


#include <list>

#include "GameObject.h"


class GameObjectList : public std::list<GameObject *> {
private:
    //std::list<GameObject> container;
public:
    GameObjectList() = default;

    GameObjectList(GameObjectList &src);

    GameObjectList(std::list<GameObject *> lst);

    GameObjectList &ofDevotion(UnitDevotion unitDevotion, bool inclusive = true);

    GameObjectList &ofClass(UnitClass unitClass, bool inclusive = true);

    GameObjectList &ofType(UnitType unitType, bool inclusive = true);


};


#endif //PROJ_GAMEOBJECTLIST_H
