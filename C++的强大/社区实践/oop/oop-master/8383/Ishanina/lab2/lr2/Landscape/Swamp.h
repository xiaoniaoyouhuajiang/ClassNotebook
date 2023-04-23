//
// Created by Mila
//

#ifndef UNTITLED_SWAMP_H
#define UNTITLED_SWAMP_H


#include "Landscape.h"

class Swamp: public Landscape {

public:
    Swamp();

    char whatYouName() override; //метод для отображения ландшафта на поле как специальной буквы
    LandscapeInterface* copy() override;//метод копирования
    void updateUnitHealth(int* healthUnit, char nameUnit) override;
    //~Swamp();

};


#endif //UNTITLED_SWAMP_H
