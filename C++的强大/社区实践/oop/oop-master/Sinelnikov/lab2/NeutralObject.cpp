//
// Created by max on 06.03.20.
//

#include "NeutralObject.h"

Unit* NeutralObject::operator+(Unit* unit){
    this->communication(unit);
    return unit;
}