#include "unit.h"

#include "cmath"

Unit::Unit()
{
    damage = 0;
    movementRadius = 0;
    attackRadius = 0;
    shieldEnabled = false;
}

Unit::~Unit() {}

bool Unit::canMove(int x, int y) {
    if (Object::canMove(x,y)) {
        int l = abs(x - this->x) + abs(y - this->y);
        if (l <= this->movementRadius) return true;
    }
    return false;
}

void Unit::attachObserver(IObserver* observer) {
    _observers.push_back(observer);
    //observer->observingObject = this;
}

void Unit::detachObserver(IObserver* observer) {
    _observers.remove(observer);
}

void Unit::notify(std::string message) {
    std::list<IObserver*>::iterator iterator = _observers.begin();
    while (iterator != _observers.end()) {
        (*iterator)->update(message);
        ++iterator;
    }
}
