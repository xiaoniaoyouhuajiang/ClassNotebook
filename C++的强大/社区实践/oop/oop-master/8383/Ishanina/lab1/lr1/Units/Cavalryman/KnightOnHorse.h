//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_KNIGHTONHORSE_H
#define UNTITLED_KNIGHTONHORSE_H


#include "Cavalryman.h"

class KnightOnHorse: public Cavalryman {
public:
    KnightOnHorse();
    virtual void whatYouName();
    ObjectInterface* copy() override;
};


#endif //UNTITLED_KNIGHTONHORSE_H
