#include "subject.h"

void Subject::deleteObserver(Observer *observer)
{
    for(std::vector<Observer*>::iterator iter = observers.begin(); iter != observers.end(); iter++){
        if (*iter == observer){
            observers.erase(iter);
            break;
        }
    }
}

void Subject::addObserver(Observer *observer)
{
    observers.push_back(observer);
}

void Subject::notify()
{
    for (Observer* obs : observers)
        obs->update(this);
}
