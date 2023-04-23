//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "ElfOnUnicorn.h"
#include "../../Base/Base.h"

ElfOnUnicorn::ElfOnUnicorn(): Cavalryman() {
    Cavalryman::health = 100;
    Cavalryman::armor = 30;
    Cavalryman::damage = 70;
    Cavalryman::name = 'E';
}

char ElfOnUnicorn::whatYouName() {
    return name;
}

ObjectInterface *ElfOnUnicorn::copy() {
    return new ElfOnUnicorn(*this);
}

ElfOnUnicorn::~ElfOnUnicorn() {
    observer->handleEvent(numberInArray);

}
