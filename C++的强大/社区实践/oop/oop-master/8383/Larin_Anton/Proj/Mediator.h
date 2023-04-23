//
// Created by anton on 3/2/20.
//

#ifndef PROJ_MEDIATOR_H
#define PROJ_MEDIATOR_H

#include <iostream>
//#include <map>
#include <vector>

#include "UnitProps.h"
//#include "GameObject.h"
//#include "GameObjectList.h"
#include "FieldCellProxy.h"
class GameObjectList;

class GameObject;

//class LandscapeProxy;

//class FieldCellProxy;

class Field;

class CommonFactory;

class Observer;

class Mediator {
private:
    Field *field;
    CommonFactory *commonFactory;
    Observer *observer;

    void init();

public:
    Mediator(int fieldWidth, int fieldHeigh);

    Mediator(Field *field1);

    void setObserver(Observer *observer1);

    Observer *getObserver();

    void createObserver();

    GameObjectList getGameObjectList();

    void getSize(int &width, int &height);

    GameObject *getObjAt(int x, int y);

    LandscapeProxy getLandscapeAt(int x, int y);

    FieldCellProxy getFieldCellAt(int x, int y);

    bool moveObj(int x1, int y1, int x2, int y2);

    int getGirdleAt(int x, int y);

    UnitDevotion getColorAt(int x, int y);

    int getOrdAt(int x, int y, UnitDevotion side);

    bool createAt(UnitClass unitClass, UnitDevotion devotion, int x, int y);

    bool destroyAt(int x, int y);


    void getGodPowers(UnitDevotion godSide, bool &allyColour, bool &enemyColour);

    void changeGodPowers(UnitDevotion godSide, UnitDevotion powerSide, bool power);
    //goDeath(GameObject* go);
};


#endif //PROJ_MEDIATOR_H
