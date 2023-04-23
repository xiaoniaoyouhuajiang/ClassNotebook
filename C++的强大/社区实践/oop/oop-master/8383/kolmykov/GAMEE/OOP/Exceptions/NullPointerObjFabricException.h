#ifndef NULLPOINTEROBJFABRICEXCEPTION_H
#define NULLPOINTEROBJFABRICEXCEPTION_H


#include <ostream>


class NullPointerObjFabricException
{
public:
    NullPointerObjFabricException();
    friend std::ostream& operator<< (std::ostream &out, const NullPointerObjFabricException exeption);
};

#endif // NULLPOINTEROBJFABRICEXCEPTION_H
