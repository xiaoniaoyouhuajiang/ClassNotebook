#ifndef INC_1_LAB_UNITOBSERVER_H
#define INC_1_LAB_UNITOBSERVER_H

#include "../Unit/Unit.h"

class Unit;

class UnitObserver {

 public:
  virtual void onUnitAttack(Unit *unit, Unit *other) = 0;
  virtual void onUnitMoved(Unit *unit, Point p) = 0;
  virtual void onUnitDestroyed(Unit *unit) = 0;
  virtual void onUnitDamaged(Unit *unit) = 0;
  virtual void onUnitHealed(Unit *unit) = 0;
};

#endif //INC_1_LAB_UNITOBSERVER_H
