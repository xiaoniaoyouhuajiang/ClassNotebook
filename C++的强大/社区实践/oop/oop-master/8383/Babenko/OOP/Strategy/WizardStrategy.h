#ifndef INC_1_LAB_WIZARDSTRATEGY_H
#define INC_1_LAB_WIZARDSTRATEGY_H

#include "NeutralObjectStrategy.h"

class WizardStrategy : public NeutralObjectStrategy {
 public:
  int getUnitTypeCoef() override {
    return 2;
  }
};

#endif //INC_1_LAB_WIZARDSTRATEGY_H
