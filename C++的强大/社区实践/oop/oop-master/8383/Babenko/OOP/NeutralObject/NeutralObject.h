#ifndef LAB2_OOP_NEUTRALOBJECT_H
#define LAB2_OOP_NEUTRALOBJECT_H

#include "../Strategy/NeutralObjectStrategy.h"
#include "../GameObject.h"

class Unit;

class NeutralObject : public GameObject {
 protected:
  NeutralObjectStrategy *objectStrategy;

 public:
  NeutralObject() : GameObject(ObjectType::NEUTRAL_OBJECT) {}
  void setStrategy(NeutralObjectStrategy *strategy) {
    this->objectStrategy = strategy;
  }
  virtual void applyTo(Unit &unit) = 0;

  virtual ~NeutralObject() {
    delete objectStrategy;
  }
};

#endif //LAB2_OOP_NEUTRALOBJECT_H
