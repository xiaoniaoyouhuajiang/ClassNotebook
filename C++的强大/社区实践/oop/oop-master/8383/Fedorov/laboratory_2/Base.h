#ifndef BASE_H
#define BASE_H
//#include <vector>
#include "GameObj.h"
#include "Observer.h"
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
  public:
    bool isNotLimit();
    virtual void addUnit(Unit* unit);
    virtual void removeUnit(Unit* unit);
    virtual int getSpace() override;
    Base(int,int);
    virtual void updateNotify(Unit* unit, Event event) override;
    virtual Unit* createUnit(Event type);
    virtual ~Base();
};

#endif // BASE_H
