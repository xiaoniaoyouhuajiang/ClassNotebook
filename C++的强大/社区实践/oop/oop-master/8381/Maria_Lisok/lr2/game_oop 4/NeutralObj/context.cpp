#include "context.h"


Context::Context(NeutralObj *obj):obj(obj)
{

}

Context::~Context()
{
    delete obj;
}

void Context::setObj(NeutralObj * obj)
{
    delete this->obj;
    this->obj = obj;
}

void Context::operator+=(Unit & unit)
{
    obj ->operator+=(unit);
}
