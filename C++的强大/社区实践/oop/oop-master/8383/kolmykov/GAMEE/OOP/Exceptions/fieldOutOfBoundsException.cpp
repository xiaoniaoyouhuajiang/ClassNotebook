#include "fieldOutOfBoundsException.h"


FieldOutOfBoundsException::FieldOutOfBoundsException(int x, int y): x(x), y(y) {

}


std::ostream& operator<< (std::ostream &out, const FieldOutOfBoundsException exeption) {
    out << "FieldOutOfBoundsException! Unacceptable coords: " << exeption.x << " " << exeption.y;
    return out;
}
