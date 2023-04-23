#ifndef NULLPOINTERMEDIATORINUNITEXCEPTION_H
#define NULLPOINTERMEDIATORINUNITEXCEPTION_H

#include <ostream>


class NullPointerMediatorInUnitException
{
private:
    int x;
    int y;
public:
    NullPointerMediatorInUnitException(int x, int y);
    friend std::ostream& operator<< (std::ostream &out, const NullPointerMediatorInUnitException exeption);
};

#endif // NULLPOINTERMEDIATORINUNITEXCEPTION_H
