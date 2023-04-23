//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "ElfOnUnicorn.h"

ElfOnUnicorn::ElfOnUnicorn(): Cavalryman() {
    Cavalryman::health = 100;
    Cavalryman::armor = 30;
    Cavalryman::damage = 70;
    Cavalryman::name = 'E';
}

void ElfOnUnicorn::whatYouName() {
    std::cout<< name;
}

ObjectInterface *ElfOnUnicorn::copy() {
    return new ElfOnUnicorn(*this);
}
