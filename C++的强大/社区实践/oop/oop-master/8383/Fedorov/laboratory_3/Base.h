#ifndef BASE_H
#define BASE_H
#include "GameObj.h"
#include "Observer.h"
#include "Event.h"
class AFactory;

class Base : public Observer, public GameObj
{
  protected:
    AFactory* factory_;
    std::vector<Unit*> troop;
    int unitCount;
    bool find(Unit*, int&);
    virtual bool findRespPlace(int&,int&);
    int hitPoint;
    int unitLimit;
    Event::Relation relation;
    Event::RaceType race;
  public:
    bool isNotLimit();
    virtual void addUnit(Unit* unit);
    virtual void removeUnit(Unit* unit);
    virtual int getSpace() override;
    void loseHp(int hp);
    bool isDead();
    Event::Relation getRelation();
    Base(int,int);
    Event getInfo();
    virtual void updateNotify(Unit* unit, Event event) override;
    virtual Unit* createUnit(Event type);
    virtual ~Base();
};

#endif // BASE_H
