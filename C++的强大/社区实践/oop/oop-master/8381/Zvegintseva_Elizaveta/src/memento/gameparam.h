#ifndef PARAMFORSAVE_H
#define PARAMFORSAVE_H

#include "baseparam.h"
#include "neutralparam.h"


class GameParam
{
public:
    GameParam(unsigned width, unsigned height, unsigned limit, vector<BaseParam*> bases, vector<NeutralParam*> neutrals, vector<LandscapeType> landscape);

    unsigned getWidth() const;

    unsigned getHeight() const;

    unsigned getLimit() const;

    vector<BaseParam*> getBases() const;

    vector<NeutralParam*> getNeutrals() const;

    vector<LandscapeType> getLandscape() const;

private:
    unsigned width;
    unsigned height;
    unsigned limit;
    vector<BaseParam*> bases;
    vector<NeutralParam*> neutrals;
    vector<LandscapeType> landscape;
};

#endif // PARAMFORSAVE_H
