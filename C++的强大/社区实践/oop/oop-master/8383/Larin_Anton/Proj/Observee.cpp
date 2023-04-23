//
// Created by anton on 3/18/20.
//


#include "Observee.h"
#include "Base.h"

bool Observee::addObserver(Base *observer) {
    if (observers.count(observer))return false;
    observers.insert(observer);
    return true;
}

bool Observee::removeObserver(Base *observer) {
    if (!observers.count(observer))return true;
    observers.erase(observer);
    return true;
}

void Observee::sigKill(GameObject &src, GameObject &dst) {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        (*it)->slKill(src, dst);
    }
}

void Observee::sigDeath(const GameObject &src, GameObject &dst) {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        (*it)->slDeath(src, dst);
    }
}
