#ifndef INC_1_LAB_ARCHERSTRATEGY_H
#define INC_1_LAB_ARCHERSTRATEGY_H

#include "NeutralObjectStrategy.h"

class ArcherStrategy : public NeutralObjectStrategy {

 public:
  int getUnitTypeCoef() override {
    return 1;
  }

};

#endif //INC_1_LAB_ARCHERSTRATEGY_H
