#ifndef LAB2_OOP_BATTLEFIELD_H
#define LAB2_OOP_BATTLEFIELD_H

#include "NeutralObject.h"
#include "../Unit/Unit.h"

class Battlefield : public NeutralObject {
 protected:
  void print(std::ostream &stream) const override {
    stream << "BF";
  }

 public:
  void applyTo(Unit &unit) override {
    unit.heal(10 * objectStrategy->getUnitTypeCoef());
  }
};

#endif //LAB2_OOP_BATTLEFIELD_H
