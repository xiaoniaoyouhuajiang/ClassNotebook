#ifndef LABOOP_OBSERVER_HPP
#define LABOOP_OBSERVER_HPP

#include "Object.hpp"

class Observer : public Object{
public:
    virtual ~Observer(){};
    virtual void update(std::string newAction) = 0;
};


#endif //LABOOP_OBSERVER_HPP
