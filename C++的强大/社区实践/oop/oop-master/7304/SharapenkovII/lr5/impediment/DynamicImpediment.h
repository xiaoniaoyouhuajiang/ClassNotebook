//
// Created by smokfyz on 13.05.19.
//

#ifndef XGAME_DYNAMICIMPEDIMENT_H
#define XGAME_DYNAMICIMPEDIMENT_H

#include "Impediment.h"

class DynamicImpediment : public Impediment {

public:
    void generate() override;
};

class Rain : public DynamicImpediment {

public:
    Rain();

    void update() override;

};

class Snow : public DynamicImpediment {

public:
    Snow();

    void update() override;

};


class Fog : public DynamicImpediment {

public:
    Fog();

    void update() override;

};



#endif //XGAME_DYNAMICIMPEDIMENT_H
