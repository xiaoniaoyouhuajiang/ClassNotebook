#include "Base.h"
#include "Unit.h"
#include "AFactory.h"

//#include "PublicObj.h"
//#include "Observer.h"
#include "Event.h"
#include "Gamefield.h"

Base::Base(int hp, int lim)
: hitPoint(hp), unitLimit(lim), unitCount(0), factory_(nullptr)
{}


bool Base::find(Unit* unit, int& index)
{
  for(std::vector<Unit*>::size_type i = 0; i != troop.size(); i++, index++){
         if (troop[i] == unit) return true;
    }
    return false;
}


void Base::removeUnit(Unit* unit)
{
  int index = 0;
  if (find(unit, index)){
    troop.erase(troop.begin() + index);
    unitCount--;
  }
  else {
    /* Исключение, не нашел */
    return;
  }
}




void Base::updateNotify(Unit* unit, Event event)
{
  switch (event.type)
  {
      case Event::UNIT_DIE:
        removeUnit(unit);
        break;
      case Event::UNIT_CREATE:
        addUnit(unit);
        break;

  /*  default:
      выполнить, если ни один вариант не подошел
      break; */
    }
}



int Base::getSpace()
{
  int space = 4;          /// Размер базы
  for (int i = 0; i < troop.size(); i++)
  {
    space += troop[i]->getSpace();
  }
    return space;
}


void Base::addUnit(Unit* unit)
{
  troop.push_back(unit);
  unitCount++;
}

Base::~Base()
{
  if (factory_)
     delete factory_;
}



bool Base::isNotLimit()
{
  return unitCount < unitLimit;
}



Unit* Base::createUnit(Event event)
{
  int x,y;
  if (findRespPlace(x,y) && isNotLimit()){
  Unit* unit;
  switch (event.unitType)
  {
      case Event::UNIT_TYPE::MAGIC:
        unit = factory_->createTMagicCharacter(field_, x, y);
        break;
      case Event::UNIT_TYPE::WARRIOR:
        unit = factory_->createTBattleCharacter(field_, x, y);
        break;
      case Event::UNIT_TYPE::SIEGE:
        unit = factory_->createTSiegeCharacter(field_, x, y);
        break;
  /*  default:
      выполнить, если ни один вариант не подошел
      break; */
    }
    addUnit(unit);
    return unit;
  }
  else{
    return nullptr;
  }
}



bool Base::findRespPlace(int &x, int &y)
{
  for (int i = x_-1; i < x_+2; i++){
      for (int j = y_; j < y_+2; j++){
         if ((i==x_ && j==y_) || i<0 || j<0 || i>field_->getHeight()-1 || j>field_->getWidth()-1)
             continue;
         else if(field_->gridView[i][j] == 1 || field_->gridView[x][y] == 2){
             x = i; y = j;
             return true;
         }
      }
  }
return false;
}


