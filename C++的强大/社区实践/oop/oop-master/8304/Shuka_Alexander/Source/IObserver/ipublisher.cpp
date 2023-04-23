#include "ipublisher.h"


void IPublisher::subscribe(std::shared_ptr<ISubscriber> subscriber)
{
    subscribers.insert(subscriber);
}


void IPublisher::unSubscribe(std::shared_ptr<ISubscriber> subscriber)
{
    auto it = subscribers.find(subscriber);

    if (it != subscribers.end()) {
        subscribers.erase(it);
    }
}


void IPublisher::notify() const
{
    for (auto i : subscribers) {
        i->update();
    }
}
