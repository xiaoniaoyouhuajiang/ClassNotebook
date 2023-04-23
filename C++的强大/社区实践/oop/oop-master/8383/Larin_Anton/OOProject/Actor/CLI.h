//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_CLI_H
#define OOPROJECT_CLI_H

#include <iostream>
#include <vector>

#include "Actor.h"

class CLI: public Actor {
public:
    //CLI();

    CLI(const std::string &name);



    void notify(std::string str) override;

    void sel();

    void turn() override;

    void draw();

    void iSummon();
    void iSelect();
    void iInteract();
    void iExit();
    void iRestart();
};


#endif //OOPROJECT_CLI_H
