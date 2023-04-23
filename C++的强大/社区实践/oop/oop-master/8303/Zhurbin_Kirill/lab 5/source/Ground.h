#ifndef OOP1_GROUND_H
#define OOP1_GROUND_H

#include "Landscape.h"

class Ground: public Landscape{
public:
    Ground(){
   
    }

    std::string getNameLandscape() override{
        return "g";
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

#endif //OOP1_GROUND_H
