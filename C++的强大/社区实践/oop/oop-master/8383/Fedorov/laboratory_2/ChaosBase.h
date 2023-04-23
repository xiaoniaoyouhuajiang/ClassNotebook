#ifndef CHAOSBASE_H
#define CHAOSBASE_H

#include "Base.h"

class ChaosBase : public Base
{
public:
  ChaosBase(GameField* field, int x, int y);
  virtual ~ChaosBase();
};

#endif // CHAOSBASE_H
