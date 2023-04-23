#ifndef LAB2_BASEMEDIATOR_H
#define LAB2_BASEMEDIATOR_H

#include "BaseComponent.h"
class BaseComponent;
class BaseMediator {
public:
    virtual void make_action() const = 0;
    virtual ~BaseMediator() {};
};


#endif
