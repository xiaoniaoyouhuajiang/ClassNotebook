#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

class Mediator;

class BaseComponent
{
public:
    BaseComponent(Mediator *mediator = nullptr) : mediator(mediator){}
    Mediator* mediator;
    void setMediator(Mediator* medi)
    {
        this->mediator = medi;
    }
};

#endif // BASECOMPONENT_H
