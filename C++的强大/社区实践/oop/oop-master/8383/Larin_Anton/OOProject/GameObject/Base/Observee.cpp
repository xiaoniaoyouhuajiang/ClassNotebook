//
// Created by anton on 5/27/20.
//

#include "Observee.h"

#include "Base.h"
#include "../../Exeptions/BaseNotSetException.h"

//Observee::Observee(const std::shared_ptr<Base> &lightBase) : lightBase(lightBase) {}

void Observee::notifyDeath() {
    if(base) {
        base->slObserveeDeath(this);
    }
    else{
        throw BaseNotSetException("Observee",Devotion::Neuter);
    }
}

void Observee::setBase(std::shared_ptr<Base> base) {
    this->base=base;
    base->addObservee(this);
}
