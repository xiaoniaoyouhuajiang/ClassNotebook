#ifndef HUMANBASE_H
#define HUMANBASE_H

#include "Base.h"

class HumanBase : public Base
{
public:
  HumanBase(GameField* field, int x, int y, Event::Relation relation = Event::FRIEND);
  virtual ~HumanBase();
};

#endif // HUMANBASE_H
