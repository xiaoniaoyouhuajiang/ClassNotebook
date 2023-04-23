#ifndef subject_hpp
#define subject_hpp

#include "observerInterface.hpp"

#include <stdio.h>
#include <set>
#include <memory>


class ObserverSubject
{
public:
    virtual void addObserver(std::shared_ptr<ObserverInterface> observer);
    virtual void removeObserver(std::shared_ptr<ObserverInterface> observer);
    virtual void notifyObservers() const;

private:
    std::set<std::shared_ptr<ObserverInterface>> observerCollection;
};

#endif /* subject_hpp */
