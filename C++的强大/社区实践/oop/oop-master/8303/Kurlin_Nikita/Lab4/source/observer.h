#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer{
public:
    virtual ~Observer(){}
    virtual void update(Subject* subject) = 0;
};

#endif // OBSERVER_H
