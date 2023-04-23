//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_BASENOTSETEXCEPTION_H
#define OOPROJECT_BASENOTSETEXCEPTION_H


#include <ostream>

class BaseNotSetException {
public:
    BaseNotSetException(const std::string &where, Devotion devotion) : where(where), devotion(devotion) {}

    friend std::ostream &operator<<(std::ostream &os, const BaseNotSetException &exception) {
        os <<(exception.devotion==Devotion ::Light?"Light ":(exception.devotion==Devotion::Dark?"Dark ":""))<<"Base at:\""+exception.where+"\" was not set, or set to nullptr";
        return os;
    }

private:
    std::string where;
    Devotion devotion;
public:
    void setDevotion(Devotion devotion) {
        BaseNotSetException::devotion = devotion;
    }

};


#endif //OOPROJECT_BASENOTSETEXCEPTION_H
