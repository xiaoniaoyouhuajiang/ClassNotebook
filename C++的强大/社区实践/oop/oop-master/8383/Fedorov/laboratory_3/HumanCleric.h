#ifndef HUMANCLERIC_H
#define HUMANCLERIC_H

#include "TMagicCharacter.h"


class HumanCleric : public TMagicCharacter{
   private:
     void initVariables();
   public:
     GameObj* copy(GameField* field);
     HumanCleric(const HumanCleric& obj);
     HumanCleric(GameField* field, int x, int y);
     virtual ~HumanCleric() {}
};


#endif // HUMANCLERIC_H
