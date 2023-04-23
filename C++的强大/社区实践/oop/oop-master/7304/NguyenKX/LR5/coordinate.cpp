#include "coordinate.h"
#include <iostream>
#include "myexception.h"

std::ostream& operator<<(std::ostream &os, Coordinate &obj){
    return os<<obj.x<<','<< obj.y;
}

std::istream& operator>>(std::istream &is, Coordinate &obj){
    char c;
    is>>obj.x>>c>>obj.y;
    if(is.fail()){
        is.clear();
        throw InputFormatException();
    }
    return is;
}
