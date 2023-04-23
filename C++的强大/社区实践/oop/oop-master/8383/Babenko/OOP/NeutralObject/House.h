#ifndef LAB2_OOP_HOUSE_H
#define LAB2_OOP_HOUSE_H

#include "NeutralObject.h"
#include "../Unit/Unit.h"

class House : public NeutralObject {
 protected:
  void print(std::ostream &stream) const override {
    stream << "H";
  }

 public:
  void applyTo(Unit &unit) override {
    unit.heal(50 * objectStrategy->getUnitTypeCoef());
  }
};

#endif //LAB2_OOP_HOUSE_H
