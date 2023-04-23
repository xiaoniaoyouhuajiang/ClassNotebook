#include "SubjectInterface.h"



SubjectInterface::SubjectInterface()
{
}


SubjectInterface::~SubjectInterface()
{
}

void SubjectInterface::registerObserever(std::shared_ptr<ObserverInterface> observer)
{
}

void SubjectInterface::removeObserver(std::shared_ptr<ObserverInterface> observer)
{
}

void SubjectInterface::notifyObservers()
{
}

void SubjectInterface::notifyAboutKill()
{
}
