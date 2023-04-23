//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_AI_H
#define OOPROJECT_AI_H

#include "Actor.h"

class AI: public Actor {
public:
    AI(const std::string &name);

    void notify(std::string string) override;

    void turn() override;

};


#endif //OOPROJECT_AI_H
