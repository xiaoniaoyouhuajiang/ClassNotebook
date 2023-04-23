#include "cliffProxy.h"

CliffProxy::CliffProxy()
{
    _landscape = new Cliff();
}
CliffProxy::~CliffProxy() {
    delete _landscape;
}

std::string CliffProxy::symb() {
    return _landscape->symb;
}

IStrategy* CliffProxy::action() {
    return _landscape->action;
}

Cliff* CliffProxy::getCliff() {
    return _landscape;
}
