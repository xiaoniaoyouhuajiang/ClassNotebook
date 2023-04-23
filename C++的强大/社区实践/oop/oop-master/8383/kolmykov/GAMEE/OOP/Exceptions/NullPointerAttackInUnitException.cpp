#include "NullPointerAttackInUnitException.h"

NullPointerAttackInUnitException::NullPointerAttackInUnitException(int x, int y): x(x), y(y)
{

}

std::ostream& operator<< (std::ostream &out, const NullPointerAttackInUnitException exeption) {
    out << "NullPointerAttackInUnitException! In unit with coords " << exeption.x << " " << exeption.y;
    return out;
}
