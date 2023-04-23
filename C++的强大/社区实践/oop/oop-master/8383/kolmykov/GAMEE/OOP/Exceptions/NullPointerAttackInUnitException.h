#ifndef NULLPOINTERATTACKINUNITEXCEPTION_H
#define NULLPOINTERATTACKINUNITEXCEPTION_H


#include <ostream>


class NullPointerAttackInUnitException
{
private:
    int x;
    int y;
public:
    NullPointerAttackInUnitException(int x, int y);
    friend std::ostream& operator<< (std::ostream &out, const NullPointerAttackInUnitException exeption);
};

#endif // NULLPOINTERATTACKINUNITEXCEPTION_H
