#ifndef OBSERVER_H
#define OBSERVER_H
class Unit;
class Event;

class Observer
{
 public:
  virtual ~Observer();
  virtual void updateNotify(Unit* someone, Event event) = 0;
};

#endif // OBSERVER_H
