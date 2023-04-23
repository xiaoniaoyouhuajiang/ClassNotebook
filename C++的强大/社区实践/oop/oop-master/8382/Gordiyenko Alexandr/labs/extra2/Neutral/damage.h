#ifndef LABS_DAMAGE_H
#define LABS_DAMAGE_H

#include "neutralObject.h"



class incDamage {
public:
    virtual void action(Unit *unit) = 0;
};

class incDamageDay : public incDamage{
    void action(Unit *unit){
        unit->param.damage += 1;
        std::cout<<"damage has been increased(day)";
    }
};

class indDamageNight: public incDamage {
    void action(Unit *unit) {
        unit->param.damage += 10;
        std::cout<<"damage has been increased(night)";
    }
};

class incDamageAction : public NeutralObject{
public:
    incDamageAction(incDamage *strategy){
        incdamage = strategy;
    }
private:
    incDamage *incdamage;

    void action(Unit *unit) {
        incdamage->action(unit);
    }

    char typeNeutral(){
        return '1';
    }

};

#endif //LABS_DAMAGE_H
