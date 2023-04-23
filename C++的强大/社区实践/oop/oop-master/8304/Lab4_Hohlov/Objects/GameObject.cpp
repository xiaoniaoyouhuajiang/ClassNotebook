#include "GameObject.h"

std::ostream &operator<<(std::ostream &stream, const GameObject &object){

    object.print(stream);
    return stream;

}