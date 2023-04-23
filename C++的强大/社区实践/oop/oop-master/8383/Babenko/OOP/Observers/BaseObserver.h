#ifndef INC_1_LAB_BASEOBSERVER_H
#define INC_1_LAB_BASEOBSERVER_H

#include "../Unit/Unit.h"

class Unit;

class BaseObserver {
 public:
  virtual void onBaseNewUnitCreated(Unit *unit, Point position) = 0;
};

#endif //INC_1_LAB_BASEOBSERVER_H
