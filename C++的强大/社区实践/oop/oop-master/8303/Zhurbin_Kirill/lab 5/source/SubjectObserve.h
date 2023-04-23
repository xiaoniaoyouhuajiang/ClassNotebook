#ifndef OOP1_SUBJECTOBSERVE_H
#define OOP1_SUBJECTOBSERVE_H


#include <vector>
#include "Observer.h"

class SubjectObserve{
public:
    std::vector<Observer*> masObserver;
   void addObserver(Observer* observer);
   void removeObserver(Observer* observer);
   void notify();

};

#endif //OOP1_SUBJECTOBSERVE_H
