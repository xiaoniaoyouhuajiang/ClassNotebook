
#ifndef UNTITLED13_BASEOBSERVER_H
#define UNTITLED13_BASEOBSERVER_H

class BaseObserver {

public:
    virtual void onBaseNewUnitCreated(Unit *unit, Point position)=0;

};


#endif //UNTITLED13_BASEOBSERVER_H
