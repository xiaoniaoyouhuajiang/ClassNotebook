#include <iostream>
#include "ObjectID.hpp"


int ObjectID::currentID = 0;

ObjectID::ObjectID() : ID(currentID) { currentID++; } ;

ObjectID ObjectID::getObjectID() const {
    ObjectID tmp(*this);
    return tmp;
}

bool ObjectID::operator==(ObjectID const &rhs){
    std::cout << "Call operator== of ObjectID\n";
    if (this->ID == rhs.ID)
        return true;
    else
        return false;
}

int ObjectID::getNumberID() const {
    return ID;
}

std::ostream& operator<<(std::ostream &out, ObjectID obj){
    out << "ID number is: " << obj.ID << std::endl;
    return out;
}