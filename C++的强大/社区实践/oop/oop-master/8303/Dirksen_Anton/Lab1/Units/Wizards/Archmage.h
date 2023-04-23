//
// Created by mensch on 11.03.2020.
//

#ifndef OOP_LABS_ARCHMAGE_H
#define OOP_LABS_ARCHMAGE_H


#include "Wizard.h"

class Archmage : public Wizard{
public:
    Archmage();
    Texture texture() const override;
};


#endif //OOP_LABS_ARCHMAGE_H
