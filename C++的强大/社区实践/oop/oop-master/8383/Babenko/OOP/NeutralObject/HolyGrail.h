#ifndef LAB2_OOP_HOLYGRAIL_H
#define LAB2_OOP_HOLYGRAIL_H

#include "NeutralObject.h"
#include "../Unit/Unit.h"

class HolyGrail : public NeutralObject {
 protected:
  void print(std::ostream &stream) const override {
    stream << "HG";
  }

 public:
  void applyTo(Unit &unit) override {
    unit.heal(100 * objectStrategy->getUnitTypeCoef());
  }
};

#endif //LAB2_OOP_HOLYGRAIL_H
