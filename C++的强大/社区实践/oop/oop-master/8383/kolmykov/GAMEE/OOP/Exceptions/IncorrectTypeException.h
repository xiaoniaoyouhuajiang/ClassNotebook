#ifndef INCORRECTTYPEEXCEPTION_H
#define INCORRECTTYPEEXCEPTION_H


#include <ostream>


class IncorrectTypeException
{
public:
    IncorrectTypeException();
    friend std::ostream& operator<< (std::ostream &out, const IncorrectTypeException exeption);
};

#endif // INCORRECTTYPEEXCEPTION_H
