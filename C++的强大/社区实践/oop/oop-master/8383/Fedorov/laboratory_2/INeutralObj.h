#ifndef INEUTRALOBJ_H
#define INEUTRALOBJ_H
#include "GameObj.h"

class INeutralObj : public GameObj
{
 public:
  virtual void updateState() = 0;
  bool isNeutral() override;

  //void selfDestr() = 0;
  //virtual void update() = 0;
  virtual ~INeutralObj();
};
#endif // INEUTRALOBJ_H
