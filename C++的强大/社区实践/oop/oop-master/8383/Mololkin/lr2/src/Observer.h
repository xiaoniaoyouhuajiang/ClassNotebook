#pragma once
#include <vector>

class IUnit;
enum class Event
{
	UNIT_KILL,
	UNIT_CREATE,
};

class Observer {
public:
	virtual void updateNotify(IUnit* unit, Event event) = 0;
};


class ObserverManager {
private:
	std::vector<Observer*> observers;
public:
	ObserverManager() = default;
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notify(IUnit* unit, Event event);
};