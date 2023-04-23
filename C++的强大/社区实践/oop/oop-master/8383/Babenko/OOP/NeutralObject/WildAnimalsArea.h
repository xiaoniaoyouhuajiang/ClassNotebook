#ifndef LAB2_OOP_WILDANIMALSAREA_H
#define LAB2_OOP_WILDANIMALSAREA_H

#include "NeutralObject.h"
#include "../Unit/Unit.h"
#include "../Proxy/TextureProxy.h"
#include "../GameField.h"

class WildAnimalsArea : public NeutralObject {
 protected:
  void print(std::ostream &stream) const override {
    stream << "AN";
  }

 public:
  void applyTo(Unit &unit) override {
    unit.damage(4);
  }
};

#endif //LAB2_OOP_WILDANIMALSAREA_H
