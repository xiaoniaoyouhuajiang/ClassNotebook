#pragma once
#include "ObserverInterface.h"
#include <memory>


class SubjectInterface
{
public:
	SubjectInterface();
	~SubjectInterface();
	virtual void registerObserever(std::shared_ptr<ObserverInterface> observer);
	virtual void removeObserver(std::shared_ptr<ObserverInterface> observer);
	virtual void notifyObservers();
	virtual void notifyAboutKill();
};

