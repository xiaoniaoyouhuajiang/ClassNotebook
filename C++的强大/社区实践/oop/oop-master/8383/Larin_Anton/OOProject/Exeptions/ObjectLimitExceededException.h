//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_OBJECTLIMITEXCEEDEDEXCEPTION_H
#define OOPROJECT_OBJECTLIMITEXCEEDEDEXCEPTION_H


#include <ostream>

class ObjectLimitExceededException {
public:
    ObjectLimitExceededException() {}

    friend std::ostream &operator<<(std::ostream &os, const ObjectLimitExceededException &exception) {
        os<<"Field limit was xceded. Cannot create more objects";
        return os;
    }

public:



};


#endif //OOPROJECT_OBJECTLIMITEXCEEDEDEXCEPTION_H
