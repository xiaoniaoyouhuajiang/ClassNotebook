#ifndef UNITSETTINGSTATE_H
#define UNITSETTINGSTATE_H


#include "state.h"


class UnitSettingState : public State
{
public:
    UnitSettingState(Kind kind, int num, std::shared_ptr<Field> field, std::shared_ptr<Facade> facade);
    void create(int xT, int xU, UnitType type);
    void endStep();
};

#endif // UNITSETTINGSTATE_H
