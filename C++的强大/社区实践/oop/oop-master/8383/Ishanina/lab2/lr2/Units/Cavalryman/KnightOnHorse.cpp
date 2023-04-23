//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "KnightOnHorse.h"
#include "../../Base/Base.h"

KnightOnHorse::KnightOnHorse(): Cavalryman() {
    Cavalryman::health = 100;
    Cavalryman::armor = 50;
    Cavalryman::damage = 50;
    Cavalryman::name = 'H';
}
char KnightOnHorse::whatYouName() {
    return name;
}

ObjectInterface *KnightOnHorse::copy() {
    return new KnightOnHorse(*this);
}

KnightOnHorse::~KnightOnHorse() {
    observer->handleEvent(numberInArray);

}
