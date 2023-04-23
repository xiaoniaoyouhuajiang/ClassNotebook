//
// Created by mensch on 11.03.2020.
//

#ifndef OOP_LABS_DRUID_H
#define OOP_LABS_DRUID_H


#include "Wizard.h"

class Druid : public Wizard {
public:
    Druid();
    Texture texture() const override;
};


#endif //OOP_LABS_DRUID_H
