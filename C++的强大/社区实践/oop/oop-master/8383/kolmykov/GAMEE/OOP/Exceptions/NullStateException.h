#ifndef NULLSTATEEXCEPTION_H
#define NULLSTATEEXCEPTION_H


#include <ostream>


class NullStateException
{
public:
    NullStateException();
    friend std::ostream& operator<< (std::ostream &out, const NullStateException exeption);
};

#endif // NULLSTATEEXCEPTION_H
