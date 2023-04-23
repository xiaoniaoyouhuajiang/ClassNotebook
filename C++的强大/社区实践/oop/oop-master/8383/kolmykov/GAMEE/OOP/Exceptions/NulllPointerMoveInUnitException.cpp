#include "NulllPointerMoveInUnitException.h"

NulllPointerMoveInUnitException::NulllPointerMoveInUnitException(int x, int y) : x(x), y(y)
{

}


std::ostream& operator<< (std::ostream &out, const NulllPointerMoveInUnitException exeption) {
    out << "NulllPointerMoveInUnitException! In unit with coords " << exeption.x << " " << exeption.y;
    return out;
}
