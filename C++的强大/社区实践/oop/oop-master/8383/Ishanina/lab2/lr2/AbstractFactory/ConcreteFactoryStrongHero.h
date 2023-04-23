//
// Created by Mila
//

#ifndef UNTITLED_CONCRETEFACTORYSTRONGHERO_H
#define UNTITLED_CONCRETEFACTORYSTRONGHERO_H

#include "AbstractFactory.h"
#include "../Units/Artillerist/Artillerist.h"
#include "../Units/Artillerist/Archer.h"
#include "../Units/Cavalryman/Cavalryman.h"
#include "../Units/Cavalryman/KnightOnHorse.h"
#include "../Units/Infantryman/Infantryman.h"
#include "../Units/Infantryman/Knight.h"

class ConcreteFactoryStrongHero : public AbstractFactory {
public:
    Artillerist *CreateArtillerist() const override  {
        return new Archer();
    }
    Cavalryman *CreateCavalryman() const override {
        return new KnightOnHorse();
    }
    Infantryman *CreateInfantryman() const override {
        return new Knight();
    }
};

#endif //UNTITLED_CONCRETEFACTORYSTRONGHERO_H
