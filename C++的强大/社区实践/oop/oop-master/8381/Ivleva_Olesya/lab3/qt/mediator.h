#include <iostream>
#include <string>
#include <vector>
#include <list>
#pragma once
#include <factory.h>

class Mediator : public IMediator{
protected:
    vector<Unit *> all_units;

public:
    void add_unit(Unit* unit){
        all_units.push_back(unit);
    }

    int attack_unit(Item* attack_from, Item* attack_to){
        Unit *attack_fr = nullptr;
        Unit *attack_t = nullptr;
        for(unsigned int i = 0; i < all_units.size(); i++){
            // превращение из Item* в Unit*
            if (all_units[i] == attack_from)
            attack_fr = all_units[i];
            if (all_units[i] == attack_to)
            attack_t = all_units[i];
        }
        if (attack_fr != nullptr && attack_t != nullptr){
            attack_t->setHealth(attack_fr->get_nearAttack());
            if (attack_t->getHealth() > 0){
                return 1;
            }
            else {
                return 0;
            }
        }
        return 2;
    }

};
