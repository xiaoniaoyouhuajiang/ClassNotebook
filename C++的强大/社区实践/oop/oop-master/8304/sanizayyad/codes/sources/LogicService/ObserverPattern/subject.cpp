#include "subject.hpp"

void ObserverSubject::addObserver(std::shared_ptr<ObserverInterface> observer)
{
    observerCollection.insert(observer);
}


void ObserverSubject::removeObserver(std::shared_ptr<ObserverInterface> observer)
{
    auto it = observerCollection.find(observer);

    if (it != observerCollection.end()) {
        observerCollection.erase(it);
    }
}


void ObserverSubject::notifyObservers() const
{
    for (auto i : observerCollection) {
        i->update();
    }
}
