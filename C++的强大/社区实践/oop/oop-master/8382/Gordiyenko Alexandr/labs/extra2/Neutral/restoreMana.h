#ifndef LABS_RESTOREMANA_H
#define LABS_RESTOREMANA_H

#include "neutralObject.h"

class restoreMana{
public:
    virtual void action(Unit *unit)= 0;
};

class restoreManaDay : public restoreMana{
    void action(Unit *unit){
        unit->param.mana +=2;
        std::cout<<"mana +=2 (day)\n";
    }
};

class restoreManaNight : public restoreMana{
    void action(Unit *unit) {
        unit->param.mana += 12;
        std::cout<<"fuel +=12 (night)\n";
    }
};

class restoreManaAction : public NeutralObject{
public:
    restoreManaAction(restoreMana *strategy){
        restoremana = strategy;
    }
private:
    restoreMana *restoremana;

    void action(Unit *unit) {
        restoremana->action(unit);
    }

    char typeNeutral(){
        return '3';
    }
};

#endif //LABS_RESTOREMANA_H
