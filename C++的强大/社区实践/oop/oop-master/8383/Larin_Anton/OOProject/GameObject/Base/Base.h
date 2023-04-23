//
// Created by anton on 5/27/20.
//

#ifndef OOPROJECT_BASE_H
#define OOPROJECT_BASE_H

//#include <iostream>

#include <vector>
#include <memory>

#include "../Entity/Entity.h"

#include "Observee.h"


class Base:public Entity {
public:
    //Base(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int lim);

    Base(int x, int y, Devotion devotion, CommonClass objectClass, int health, EntityType entityType, int lim);

    void slObserveeDeath(Observee *observee);
    void addObservee(std::shared_ptr<Observee> observee);
    void addObservee(Observee* observee);

    bool isLim();

    CommonClass getObjectClass() override;

    void act(std::shared_ptr<GameObject> obj) override;

    void react(std::shared_ptr<GameObject> sbj) override;

    void step(std::shared_ptr<GameObject> obj) override;

    void restep(std::shared_ptr<GameObject> sbj) override;

    bool canStep(int x, int y) override;

    bool canAct(int x, int y) override;

    bool createUnit(CommonClass commonClass);



private:
    int lim;
public:
    int getLim() const;

    int getCur() const;

    void setToBeRemoved(bool toBeRemoved) override;

private:
    int cur;
    std::vector<Observee*> observees;
};


#endif //OOPROJECT_BASE_H
