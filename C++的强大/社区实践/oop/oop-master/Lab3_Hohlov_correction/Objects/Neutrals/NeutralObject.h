

#ifndef UNTITLED13_NEUTRALOBJECT_H
#define UNTITLED13_NEUTRALOBJECT_H


#include "../GameObject.h"
#include "NeutralObjectStrategy/NeutralObjectStrategy.h"

class Unit;

class NeutralObject: public GameObject {

protected:

    NeutralObjectStrategy *strategy;

public:

    NeutralObject(): GameObject(ObjectType::NEUTRAL_OBJECT){}
    void setStrategy(NeutralObjectStrategy *strategy) { this->strategy = strategy; }
    virtual void applyTo(Unit &unit)=0;

    virtual ~NeutralObject(){

        delete strategy;

    }

};


#endif //UNTITLED13_NEUTRALOBJECT_H
