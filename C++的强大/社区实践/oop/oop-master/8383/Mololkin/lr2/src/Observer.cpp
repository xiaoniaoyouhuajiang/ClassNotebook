#include "Observer.h"


void ObserverManager::addObserver(Observer* observer)
{
	observers.push_back(observer);
}

void ObserverManager::removeObserver(Observer* observer)
{
	for (auto i = observers.begin(); i < observers.end(); i++)
	{
		if (*i = observer) {
			observers.erase(i);
		}
	}
}

void ObserverManager::notify(IUnit* unit, Event event)
{
	for (unsigned int i = 0; i < observers.size(); i++) {
		observers[i]->updateNotify(unit, event);
	}
}


