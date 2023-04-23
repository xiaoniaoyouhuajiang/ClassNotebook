#ifndef HUMANBASE_H
#define HUMANBASE_H

#include "Base.h"

class HumanBase : public Base
{
public:
  HumanBase(GameField* field, int x, int y);
  virtual ~HumanBase();
};

#endif // HUMANBASE_H
