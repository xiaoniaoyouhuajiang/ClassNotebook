#ifndef PUBLICOBJ_H
#define PUBLICOBJ_H
#include <vector>

class Unit;
class Observer;
class Event;

class PublicObj
{
 private:
    std::vector<Observer*> observers_;
 public:
  virtual void addObserver(Observer* observer);
  virtual void removeObserver(Observer* observer);
  virtual ~PublicObj();
 protected:
  virtual void notify(Unit* someone, Event event);
};

#endif // PUBLICOBJ_H
