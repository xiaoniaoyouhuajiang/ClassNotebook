#include "subject.h"

void Subject::addObserver(Observer * observer)
{
    masObserver.push_back(observer);
}

void Subject::removeObserver(Observer * observer)
{
    for(std::vector<Observer*>::iterator iter = masObserver.begin(); iter != masObserver.end(); iter++){
        if(*iter == observer){
            masObserver.erase(iter);
            return;
        }
    }
}

void Subject::notify()
{
    for(Observer* el : masObserver)
        el->update(this);
}
