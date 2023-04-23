#ifndef LABOOP_SUBJECT_HPP
#define LABOOP_SUBJECT_HPP

#include "Object.hpp"
#include "Observer.hpp"

class Subject : public Object{
public:
    virtual ~Subject(){};
    virtual void addObservers(Observer *observer) = 0;
    virtual void notifyObservers(std::string *newAction) = 0;
};


#endif //LABOOP_SUBJECT_HPP
