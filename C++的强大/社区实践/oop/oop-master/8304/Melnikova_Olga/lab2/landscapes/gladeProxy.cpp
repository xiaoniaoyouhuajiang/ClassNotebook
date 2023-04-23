#include "gladeProxy.h"

GladeProxy::GladeProxy()
{
    _landscape = new Glade();
}
GladeProxy::~GladeProxy() {
    delete _landscape;
}

std::string GladeProxy::symb() {
    return _landscape->symb;
}

IStrategy* GladeProxy::action() {
    return _landscape->action;
}

Glade* GladeProxy::getGlade() {
    return _landscape;
}
