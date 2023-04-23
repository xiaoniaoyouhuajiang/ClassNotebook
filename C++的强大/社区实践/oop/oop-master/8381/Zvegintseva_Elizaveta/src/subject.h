#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

class Subject
{
protected:
    std::vector<Observer*> masObserver;
public:
    void addObserver(Observer*);
    void removeObserver(Observer*);
    void notify();
};

#endif // SUBJECT_H
