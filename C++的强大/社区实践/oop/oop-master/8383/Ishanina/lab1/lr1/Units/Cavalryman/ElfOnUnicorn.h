//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_ELFONUNICORN_H
#define UNTITLED_ELFONUNICORN_H


#include "Cavalryman.h"

class ElfOnUnicorn: public Cavalryman {
public:
    ElfOnUnicorn();
    void whatYouName() override;
    ObjectInterface* copy() override;
};


#endif //UNTITLED_ELFONUNICORN_H
