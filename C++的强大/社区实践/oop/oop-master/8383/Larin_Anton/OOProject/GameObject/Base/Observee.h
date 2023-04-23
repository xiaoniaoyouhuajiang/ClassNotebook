//
// Created by anton on 5/27/20.
//

#ifndef OOPROJECT_OBSERVEE_H
#define OOPROJECT_OBSERVEE_H

#include <memory>

class Base;

class Observee {
public:
    //Observee(const std::shared_ptr<Base> &lightBase);
    void setBase(std::shared_ptr<Base> base);

protected:
    void notifyDeath();

private:


    std::shared_ptr<Base> base;




};


#endif //OOPROJECT_OBSERVEE_H
