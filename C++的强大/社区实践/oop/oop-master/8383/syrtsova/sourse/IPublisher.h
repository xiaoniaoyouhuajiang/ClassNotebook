#pragma once
#include "iobserver.h"
#include <string>



class IPublisher    
{                   
public:
	virtual void attachObserver(IObserver* observer) = 0;
	virtual void detachObserver(IObserver* observer) = 0;
	virtual void notify(std::string message) = 0;
	virtual ~IPublisher();
};