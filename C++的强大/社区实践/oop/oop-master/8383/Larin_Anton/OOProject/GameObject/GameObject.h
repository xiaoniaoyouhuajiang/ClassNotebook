//
// Created by anton on 5/9/20.
//

#ifndef OOPROJECT_GAMEOBJECT_H
#define OOPROJECT_GAMEOBJECT_H

#include <memory>
#include <string>
#include <utility>

#include "../Stats.h"
#include "Vitality.h"


class Mediator;

class GameObject {

private:
    int x;
    int y;


    Devotion devotion;
    GameObjectFlyWeight* flyWeight;

    Vitality vitality;
    ObjectType objectType;
    CommonClass objectClass;
    std::shared_ptr<Mediator> mediator;
protected:
    bool toBeRemoved;
public:

    GameObject(int x, int y, bool toBeRemoved, Devotion devotion, ObjectType objectType, CommonClass objectClass,
               int health, int armour, float dmgmul);

    virtual GameObjectFlyWeight * getFlyWeight();

    virtual void setFlyWeight(GameObjectFlyWeight *flyWeight);


    const std::shared_ptr<Mediator> &getMediator() const;

    void setMediator(const std::shared_ptr<Mediator> &mediator);


    bool isToBeRemoved() const;

    virtual void setToBeRemoved(bool toBeRemoved);

    std::pair<int, int> getCoords();

    void setCoords(int x, int y);

    void setCoords(std::pair<int, int>);

    Vitality &getVitality();

    Devotion getDevotion() const;

    virtual void act(std::shared_ptr<GameObject> obj) = 0;

    virtual void react(std::shared_ptr<GameObject> sbj) = 0;

    virtual void step(std::shared_ptr<GameObject> obj) = 0;

    virtual void restep(std::shared_ptr<GameObject> sbj) = 0;

    virtual bool canStep(int x, int y) = 0;

    virtual bool canAct(int x, int y) = 0;

    virtual CommonClass getObjectClass() = 0;



};


#endif //OOPROJECT_GAMEOBJECT_H
