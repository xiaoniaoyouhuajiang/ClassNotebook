#include "IncorrectTypeException.h"

IncorrectTypeException::IncorrectTypeException()
{

}


std::ostream& operator<< (std::ostream &out, const IncorrectTypeException exeption) {
    out << "IncorrectTypeException!";
    return out;
}
