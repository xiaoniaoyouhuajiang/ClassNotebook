#include "ChaosBase.h"
#include "globalconst.h"
#include "ChaosFactory.h"




ChaosBase::ChaosBase(GameField* field, int x, int y)
 : Base(CHAOS_BASE_HP, CHAOS_BASE_LIMIT)
 {
  character = CHAOS_BASE_VIEW;
  factory_ = new ChaosFactory;
  setPosition(field, x, y);
 }





ChaosBase::~ChaosBase()
{

}
