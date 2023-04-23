#ifndef TROLSMAGIC_H
#define TROLSMAGIC_H
#include "TMagicCharacter.h"



class TrolsMagic : public TMagicCharacter{
   private:
     void initVariables();
   public:
      TrolsMagic(const TrolsMagic& obj);
      GameObj* copy(GameField* field);
      TrolsMagic(GameField* field, int x, int y);
      virtual ~TrolsMagic() {}
};

#endif // TROLSMAGIC_H
