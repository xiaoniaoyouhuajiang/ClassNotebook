//
// Created by anton on 5/9/20.
//

#ifndef OOPROJECT_UNIT_H
#define OOPROJECT_UNIT_H


#include "../GameObject.h"
#include "../../GameObject/Base/Observee.h"



#include "../Entity/Entity.h"

#include "../Ability.h"
#include "../Mobility.h"

class Unit: public GameObject, public Observee {
public:
    Unit(int x, int y, Devotion devotion, CommonClass objectClass, int health, int armour, float dmgmul,
         int abPower, int abRange, int mbAgility, int mbRange, UnitType unitClass);

    void act(std::shared_ptr<GameObject> obj) override;

    void react(std::shared_ptr<GameObject> sbj) override;

    void step(std::shared_ptr<GameObject> obj) override;

    void restep(std::shared_ptr<GameObject> sbj) override;

    bool canStep(int x, int y) override;

    bool canAct(int x, int y) override;

    Ability &getAbility();

    Mobility &getMobility();

    void setToBeRemoved(bool toBeRemoved) override;


    friend GameObject& operator+= (GameObject& lv,  Unit& rv){
        auto lvPtr = std::shared_ptr<GameObject>(&lv);
        rv.act(std::move(lvPtr));
    }

    friend std::shared_ptr<GameObject>& operator+= (std::shared_ptr<GameObject>& lv,  std::shared_ptr<Unit>& rv){
        rv->act(lv);
        return lv;
    }

    friend std::shared_ptr<Entity>& operator+= (std::shared_ptr<Entity>& lv,  std::shared_ptr<Unit>& rv){
        rv->act(std::static_pointer_cast<GameObject>(lv));
        return lv;
    }
/*
    friend GameObject& operator+= (Unit& lv,  Unit& rv){
        auto lvPtr = std::shared_ptr<GameObject>(&lv);
        rv.act(lvPtr);
    }*/
//protected: CommonClass getObjectClass() override;

private:
    Ability ability;
    Mobility mobility;
    UnitType unitClass;
protected:
    bool blocked;
public:
    bool isBlocked() const;
    void setBlocked(bool blocked);


};


#endif //OOPROJECT_UNIT_H
