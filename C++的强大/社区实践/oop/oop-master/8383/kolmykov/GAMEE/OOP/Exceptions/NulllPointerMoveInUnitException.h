#ifndef NULLLPOINTERMOVEINUNITEXCEPTION_H
#define NULLLPOINTERMOVEINUNITEXCEPTION_H


#include <ostream>


class NulllPointerMoveInUnitException
{
private:
    int x;
    int y;
public:
    NulllPointerMoveInUnitException(int x, int y);
    friend std::ostream& operator<< (std::ostream &out, const NulllPointerMoveInUnitException exeption);
};

#endif // NULLLPOINTERMOVEINUNITEXCEPTION_H
