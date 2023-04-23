//
// Created by Mila
//

#ifndef UNTITLED_CONCRETEFACTORYMAGICHERO_H
#define UNTITLED_CONCRETEFACTORYMAGICHERO_H

#include "AbstractFactory.h"
#include "../Units/Artillerist/Artillerist.h"
#include "../Units/Cavalryman/Cavalryman.h"
#include "../Units/Cavalryman/ElfOnUnicorn.h"
#include "../Units/Infantryman/Infantryman.h"
#include "../Units/Artillerist/Magician.h"
#include "../Units/Infantryman/Gnome.h"

class ConcreteFactoryMagicHero : public AbstractFactory {
public:
    Artillerist *CreateArtillerist() const override {
        return new Magician();
    }
    Cavalryman *CreateCavalryman() const override {
        return new ElfOnUnicorn();
    }
    Infantryman *CreateInfantryman() const override {
        return new Gnome();
    }
};



#endif //UNTITLED_CONCRETEFACTORYMAGICHERO_H
