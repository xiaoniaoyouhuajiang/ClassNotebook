#ifndef IPUBLISHER_H
#define IPUBLISHER_H

#include <set>
#include <memory>

#include "isubscriber.h"


class IPublisher
{
public:
    virtual void subscribe(std::shared_ptr<ISubscriber> subscriber);
    virtual void unSubscribe(std::shared_ptr<ISubscriber> subscriber);
    virtual void notify() const;

private:
    std::set<std::shared_ptr<ISubscriber>> subscribers;
};

#endif // IPUBLISHER_H
