//
// Created by anton on 5/27/20.
//

#include "Base.h"

#include "../../Mediator.h"
//Base::Base(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int lim) : GameObject(x, y, false, devotion, ObjectType::Base, CommonClass::Base, health, armour, dmgmul), lim(lim), cur(0) {}

Base::Base(int x, int y, Devotion devotion, CommonClass objectClass, int health, EntityType entityType, int lim)
        : Entity(x, y, devotion, objectClass, health, entityType), lim(lim), cur(0) {}


void Base::slObserveeDeath(Observee *observee) {
    bool flag = false;
    for(int i = 0; i<observees.size(); i++){
        if(auto oi = observees[i]) {
            if (observee == &(*oi)) {
                observees.erase(observees.begin() + i);
                flag = true;
                break;
            }
        //TODO exceptions on else
        }
    }

    if(!flag){
        //TODO exeption observee not found
    }
    if(observees.size()==0){
        getMediator()->onUnitsDestroyed(getDevotion());
    }
    //std::cout<<"Base: observee died"<<std::endl;
}

void Base::addObservee(std::shared_ptr<Observee> observee) {
    //observees.push_back(observee);
    //std::cout<<"Base: observee added"<<std::endl;
}
void Base::addObservee(Observee* observee) {
    observees.push_back(observee);
    //std::cout<<"Base: observee added"<<std::endl;
}

CommonClass Base::getObjectClass() {
    return CommonClass::Base;
}

void Base::act(std::shared_ptr<GameObject> obj) {

}

void Base::react(std::shared_ptr<GameObject> sbj) {

}

void Base::step(std::shared_ptr<GameObject> obj) {

}

void Base::restep(std::shared_ptr<GameObject> sbj) {

}

bool Base::canStep(int x, int y) {
    return false;
}

bool Base::canAct(int x, int y) {
    return false;
}

bool Base::createUnit(CommonClass commonClass) {
    assert(classToType(commonClass)==ObjectType::Unit);
    std::pair<int,int> c = getCoords();
    return getMediator()->createObject(c.first,c.second,getDevotion(),commonClass);
}

bool Base::isLim() {
    return cur>=lim;
}

int Base::getLim() const {
    return lim;
}

int Base::getCur() const {
    return cur;
}

void Base::setToBeRemoved(bool toBeRemoved) {
    GameObject::setToBeRemoved(toBeRemoved);
    getMediator()->onBaseDestroyed(getDevotion());
}


