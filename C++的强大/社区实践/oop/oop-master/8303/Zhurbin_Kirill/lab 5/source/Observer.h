#ifndef OOP1_OBSERVER_H
#define OOP1_OBSERVER_H

class SubjectObserve;

class Observer{
public:
    virtual void update(SubjectObserve* subject) = 0;
};

#endif //OOP1_OBSERVER_H
