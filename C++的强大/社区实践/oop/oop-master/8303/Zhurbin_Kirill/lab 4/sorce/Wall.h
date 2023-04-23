#ifndef OOP1_WALL_H
#define OOP1_WALL_H

#include "Landscape.h"

class Wall: public Landscape{
public:
    Wall(){

    }

    std::string getNameLandscape() override{
        return "s";
    }

    bool isMoved(Unit* unit) override {
        if (unit->character == "soldier")
            return landscape.canMove();
        else if (unit->character == "tankman")
            return landscape.notCanMove();
        else if (unit->character == "shooter")
            return landscape.notCanMove();
    }
};

#endif //OOP1_WALL_H
