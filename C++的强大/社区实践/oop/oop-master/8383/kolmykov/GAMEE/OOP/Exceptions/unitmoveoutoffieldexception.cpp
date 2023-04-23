#include "unitmoveoutoffieldexception.h"

UnitMoveOutOfFieldException::UnitMoveOutOfFieldException(int xS, int yS, int xF, int yF): xS(xS), yS(yS), xF(xF), yF(yF)
{

}


std::ostream& operator<< (std::ostream &out, const UnitMoveOutOfFieldException exeption) {
    out << "UnitMoveOutOfFieldException! Unit tried to move from (" << exeption.xS << " ; " << exeption.yS << ") to (" << exeption.xF << " ; " << exeption.yF << ")";
    return out;
}
