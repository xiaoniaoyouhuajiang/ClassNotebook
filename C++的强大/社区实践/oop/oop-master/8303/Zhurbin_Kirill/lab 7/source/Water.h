#ifndef OOP1_WATER_H
#define OOP1_WATER_H

#include "Landscape.h"

class Water: public Landscape{
public:
    Water(){

    }

    std::string getNameLandscape() override{
        return "w";
    }

    bool isMoved(Unit* unit) override {
        if (unit->character == "soldier")
            return landscape.canMove();
        else if (unit->character == "tankman")
            return landscape.canMove();
        else if (unit->character == "shooter")
            return landscape.canMove();
    }
};

#endif //OOP1_WATER_H
