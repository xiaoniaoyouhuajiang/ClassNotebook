#ifndef UNITMOVEOUTOFFIELDEXCEPTION_H
#define UNITMOVEOUTOFFIELDEXCEPTION_H


#include <ostream>


class UnitMoveOutOfFieldException
{
private:
    int xS;
    int yS;
    int xF;
    int yF;
public:
    UnitMoveOutOfFieldException(int xS, int yS, int xF, int yF);
    friend std::ostream& operator<< (std::ostream &out, const UnitMoveOutOfFieldException exeption);
};

#endif // UNITMOVEOUTOFFIELDEXCEPTION_H
