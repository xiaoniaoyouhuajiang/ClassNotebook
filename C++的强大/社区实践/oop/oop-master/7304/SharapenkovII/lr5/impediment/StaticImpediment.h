//
// Created by smokfyz on 13.05.19.
//

#ifndef XGAME_STATICIMPEDIMENT_H
#define XGAME_STATICIMPEDIMENT_H

#include "Impediment.h"

class StaticImpediment : public Impediment {

public:
    void update() override;

};


class Mountains : public StaticImpediment {

public:
    Mountains();

    void generate() override;

};


class Forest : public StaticImpediment {

public:
    Forest();

    void generate() override;

};


class Swamp : public StaticImpediment {

public:
    Swamp();

    void generate() override;

};


class River : public StaticImpediment {

public:
    River();

    void generate() override;

};

#endif //XGAME_STATICIMPEDIMENT_H
