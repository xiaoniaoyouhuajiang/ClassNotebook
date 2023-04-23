#ifndef GOBLINCATAPULT_H
#define GOBLINCATAPULT_H

#include "TSiegeCharacter.h"

class GoblinCatapult : public TSiegeCharacter {
   private:
     void initVariables();
     int fireBall;
   public:
     GoblinCatapult(const GoblinCatapult& obj);
     GameObj* copy(GameField* field);
     void shoot() override {}
     GoblinCatapult(GameField* field, int x, int y);
     virtual ~GoblinCatapult() {}
};


#endif // GOBLINCATAPULT_H
