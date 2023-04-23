#include "NullStateException.h"

NullStateException::NullStateException()
{

}


std::ostream& operator<< (std::ostream &out, const NullStateException exeption) {
    out << "NullStateException!";
    return out;
}
