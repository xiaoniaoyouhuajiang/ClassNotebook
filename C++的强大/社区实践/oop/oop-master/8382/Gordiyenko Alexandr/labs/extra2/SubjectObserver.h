#ifndef LABS_SUBJECTOBSERVER_H
#define LABS_SUBJECTOBSERVER_H

#include <vector>
#include "Observer.h"

class SubjectObserve{
public:
    std::vector<Observer*> masObserver;
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notify();
};
#endif //LABS_SUBJECTOBSERVER_H
