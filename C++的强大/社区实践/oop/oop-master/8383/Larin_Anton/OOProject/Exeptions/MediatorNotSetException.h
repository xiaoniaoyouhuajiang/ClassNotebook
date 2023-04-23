//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_MEDIATORNOTSETEXCEPTION_H
#define OOPROJECT_MEDIATORNOTSETEXCEPTION_H

#include <string>
#include <iostream>
//#include <ostream>

class MediatorNotSetException{
public:
    MediatorNotSetException(const std::string &where) : where(where) {}

    friend std::ostream &operator<<(std::ostream &os, const MediatorNotSetException &exception) {
        os <<"Mediator at:\""+exception.where+"\" was not set, or set to nullptr";
        return os;
    }

private:
    std::string where;

};


#endif //OOPROJECT_MEDIATORNOTSETEXCEPTION_H
