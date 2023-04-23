#include "SubjectObserve.h"

void SubjectObserve::addObserver(Observer* observer) {
    masObserver.push_back(observer);
}

void SubjectObserve::removeObserver(Observer* observer) {
    std::vector<Observer*>::iterator iter = masObserver.begin();
    while(iter != masObserver.end()){
        if (*iter = observer){
            masObserver.erase(iter);
            return;
        }
    }

}

void  SubjectObserve::notify() {
    for (Observer* element: masObserver)
        element->update(this);
}