//
// Created by anton on 3/18/20.
//

#ifndef PROJ_OBSERVEE_H
#define PROJ_OBSERVEE_H

#include <set>
//#include "GameObject.h"

class GameObject;

class Base;

class Observee {
private:
    std::set<Base *> observers;
public:
    bool addObserver(Base *observer);

    bool removeObserver(Base *observer);

protected:
    void sigKill(GameObject &src, GameObject &dst);

    void sigDeath(const GameObject &src, GameObject &dst);

};


#endif //PROJ_OBSERVEE_H
