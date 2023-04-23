#include "PublicObj.h"
#include "Observer.h"
#include "Event.h"

void PublicObj::addObserver(Observer* observer)
{
  observers_.push_back(observer);
}


void PublicObj::removeObserver(Observer* observer)
{
    int index = 0;
  for(std::vector<Observer*>::size_type i = 0; i != observers_.size(); i++, index++){
         if (observers_[i] == observer)
         {
          observers_.erase(observers_.begin() + index);
          break;
         }
    }
}


void PublicObj::notify(Unit* someone, Event event)
{
  for(std::vector<Observer*>::size_type i = 0; i != observers_.size(); i++)
  {
    observers_[i]->updateNotify(someone, event);
    }
}


PublicObj::~PublicObj(){

}
