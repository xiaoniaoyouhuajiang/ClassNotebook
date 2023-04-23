#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"

class Subject
{
public:
    std::vector <Observer*> observers;
    void addObserver(Observer *);
    void deleteObserver(Observer *);
    void notify();
};

#endif // SUBJECT_H
