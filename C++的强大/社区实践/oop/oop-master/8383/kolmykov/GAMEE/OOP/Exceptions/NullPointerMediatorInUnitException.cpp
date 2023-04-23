#include "NullPointerMediatorInUnitException.h"

NullPointerMediatorInUnitException::NullPointerMediatorInUnitException(int x, int y): x(x), y(y)
{

}


std::ostream& operator<< (std::ostream &out, const NullPointerMediatorInUnitException exeption) {
    out << "NullPointerMediatorInUnitException! In unit with coords " << exeption.x << " " << exeption.y;
    return out;
}
