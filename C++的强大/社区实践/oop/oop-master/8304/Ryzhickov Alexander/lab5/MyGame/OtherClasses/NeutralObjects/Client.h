//
// Created by Alex on 12.04.2020.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H


#include "Context.h"
#include "Generators/ArmorGenerator.h"
#include "Generators/HealthGenerator.h"
#include "Generators/GoldGenerator.h"
#include "Village/Village.h"

class Client : public Context {
public:
    void useStrategy(Unit *unit) override {
        if (neutralObject != nullptr) {
            if (dynamic_cast<ArmorGenerator *> (neutralObject) != nullptr) {
                (*neutralObject)[unit->getArmorForGenerator()];
            }
            if (dynamic_cast<HealthGenerator *> (neutralObject) != nullptr) {
                (*neutralObject)[unit->getHealthForGenerator()];
            }
            if (dynamic_cast<GoldGenerator *> (neutralObject) != nullptr) {
                (*neutralObject)[unit->getMoney()];
            }
            if (dynamic_cast<Village *> (neutralObject) != nullptr) {
                (*neutralObject)[unit->getMoney()];
            }
        }
    }
    void setStrategy(NeutralObject *neutralObject1) override {
        neutralObject = neutralObject1;
    }
};


#endif //GAME_CLIENT_H
