//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_KNIGHT_H
#define UNTITLED_KNIGHT_H


#include "Infantryman.h"

class Knight: public Infantryman {
public:
    Knight();
    char whatYouName() override;
    ObjectInterface* copy() override;
    ~Knight();
};


#endif //UNTITLED_KNIGHT_H
