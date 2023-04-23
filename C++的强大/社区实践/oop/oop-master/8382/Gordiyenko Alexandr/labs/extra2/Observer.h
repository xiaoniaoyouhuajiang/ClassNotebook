#ifndef LABS_OBSERVER_H
#define LABS_OBSERVER_H

class SubjectObserve;
class Observer {
public:
    virtual void update(SubjectObserve* subject) = 0;
};

#endif //LABS_OBSERVER_H
