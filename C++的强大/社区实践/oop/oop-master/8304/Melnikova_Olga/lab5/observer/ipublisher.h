#pragma once
#include "iobserver.h"
#include <string>

class IObserver;

class IPublisher      // Компоновщик. предоставляет одинак. функции и для листов и для композита.
{                     // Интерфейс наблюдателя
public:
    virtual ~IPublisher();

    virtual void attachObserver(IObserver* observer) = 0;
    virtual void detachObserver(IObserver* observer) = 0;
    virtual void notify(std::string message) = 0;
};
