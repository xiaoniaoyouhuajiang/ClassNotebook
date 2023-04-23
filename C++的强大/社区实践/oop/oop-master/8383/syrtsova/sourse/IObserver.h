#pragma once
#include <string>

/// Интерфейс издателя
class IObserver   
{
public:
	virtual ~IObserver();
	virtual void update(std::string message) = 0;
};