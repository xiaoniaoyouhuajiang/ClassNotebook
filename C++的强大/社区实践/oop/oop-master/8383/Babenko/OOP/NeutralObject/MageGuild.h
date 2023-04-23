#ifndef LAB2_OOP_MAGEGUILD_H
#define LAB2_OOP_MAGEGUILD_H

#include "NeutralObject.h"
#include "../Unit/Wizard/FireMage.h"
#include "../Unit/Wizard/IceMage.h"
#include "../Unit/Unit.h"

class MageGuild : public NeutralObject {
 protected:
  void print(std::ostream &stream) const override {
    stream << "MG";
  }

 public:
  void applyTo(Unit &unit) override {

    if (unit.getUnitType() == UnitType::ARCHER) {
      FireMage mage;
      unit = mage;
    } else if (unit.getUnitType() == UnitType::VIKING) {
      IceMage mage;
      unit = mage;
    }
  }
};

#endif //LAB2_OOP_MAGEGUILD_H
