#ifndef CONTEXT_H
#define CONTEXT_H

#include "neutralObj.h"

class Context{
private:
    NeutralObj* obj;
public:
    Context(NeutralObj *obj=nullptr);
    ~Context();
    void setObj(NeutralObj *);
    void operator+=(Unit& unit);
};

#endif // CONTEXT_H
