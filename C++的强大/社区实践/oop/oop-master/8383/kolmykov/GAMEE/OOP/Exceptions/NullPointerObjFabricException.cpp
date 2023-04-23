#include "NullPointerObjFabricException.h"

NullPointerObjFabricException::NullPointerObjFabricException()
{

}


std::ostream& operator<< (std::ostream &out, const NullPointerObjFabricException exeption) {
    out << "NullPointerObjFabricException!";
    return out;
}
