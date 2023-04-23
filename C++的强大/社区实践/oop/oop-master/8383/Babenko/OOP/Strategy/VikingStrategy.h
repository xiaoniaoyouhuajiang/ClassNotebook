#ifndef INC_1_LAB_VIKINGSTRATEGY_H
#define INC_1_LAB_VIKINGSTRATEGY_H

#include "NeutralObjectStrategy.h"

class VikingsStrategy : public NeutralObjectStrategy {

 public:
  int getUnitTypeCoef() override {
    return 10;
  }

};

#endif //INC_1_LAB_VIKINGSTRATEGY_H
