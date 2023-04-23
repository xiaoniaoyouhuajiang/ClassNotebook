#include "swampProxy.h"

SwampProxy::SwampProxy()
{
    _landscape = new Swamp();
}
SwampProxy::~SwampProxy() {
    delete _landscape;
}

std::string SwampProxy::symb() {
    return _landscape->symb;
}

IStrategy* SwampProxy::action() {
    return _landscape->action;
}

Swamp* SwampProxy::getSwamp() {
    return _landscape;
}
