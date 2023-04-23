//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_ARCHER_H
#define UNTITLED_ARCHER_H


#include "Artillerist.h"

class Archer: public Artillerist {
public:
    Archer();

    char whatYouName() override;
    ObjectInterface* copy() override;
    ~Archer();

};


#endif //UNTITLED_ARCHER_H
