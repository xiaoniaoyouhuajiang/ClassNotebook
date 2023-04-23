#include "IncorrectFieldConstructorException.h"

IncorrectFieldConstructorException::IncorrectFieldConstructorException(int w, int h) : w(w), h(h)
{

}


std::ostream& operator<< (std::ostream &out, const IncorrectFieldConstructorException exeption) {
    out << "IncorrectFieldConstructorException! Was try to create field with width = " << exeption.w << " and height = " << exeption.h;
    return out;
}
