#ifndef OOP_CELL_H
#define OOP_CELL_H

#include "Object.h"
#include "Neutral objects/Neutral.h"
#include "Landscapes/Landscape.h"

struct cell {
    cell() {
        unit = nullptr;
        neutral = nullptr;
        type = LandscapeTypes::None;
    }

    Object* unit;
    Neutral* neutral;
    LandscapeTypes type;

};


#endif //OOP_CELL_H
