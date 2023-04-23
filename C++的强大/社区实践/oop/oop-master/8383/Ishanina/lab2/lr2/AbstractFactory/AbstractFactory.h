//
// Created by Mila
//

#ifndef UNTITLED_ABSTRACTFACTORY_H
#define UNTITLED_ABSTRACTFACTORY_H



#include "../Units/Cavalryman/ElfOnUnicorn.h"
#include "../Units/Cavalryman/KnightOnHorse.h"
#include "../Units/Infantryman/Gnome.h"
#include "../Units/Artillerist/Archer.h"
#include "../Units/Artillerist/Magician.h"
#include "../Units/Infantryman/Knight.h"



class AbstractFactory {


public:
    virtual Artillerist *CreateArtillerist() const = 0;
    virtual Cavalryman *CreateCavalryman() const = 0;
    virtual Infantryman *CreateInfantryman() const = 0;






};


#endif //UNTITLED_ABSTRACTFACTORY_H
