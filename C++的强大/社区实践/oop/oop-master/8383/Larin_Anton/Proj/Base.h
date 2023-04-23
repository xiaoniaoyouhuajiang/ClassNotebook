//
// Created by anton on 2/25/20.
//

#ifndef PROJ_BASE_H
#define PROJ_BASE_H

#include <set>


#include "UnitProps.h"
//#include "GameObject.h"

//#include "Observee.h"

class GameObject;

class Observee;

class Base {

protected:
    std::set<Observee *> observees;

private:

public:
    bool addObservee(Observee *observee);

    bool removeObservee(Observee *observee);

    virtual int getUnitLim() = 0;

    virtual void setUnitLim(int unitLim) = 0;

    virtual bool spawnAt(UnitClass unitClass, int x, int y) = 0;

    virtual void slKill(GameObject &src, GameObject &dst) const = 0;//Why is this const??

    virtual void slDeath(const GameObject &src, GameObject &dst) const = 0;
};



#endif //PROJ_BASE_H
