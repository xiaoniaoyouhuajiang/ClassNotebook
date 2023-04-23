//
// Created by Mila on 15.04.2020.
//

#ifndef UNTITLED_ABYSS_H
#define UNTITLED_ABYSS_H


#include "Landscape.h"

class Abyss: public Landscape {
public:
    Abyss();

    char whatYouName() override; //метод для отображения ландшафта на поле как специальной буквы
    LandscapeInterface* copy() override;//метод копирования
    void updateUnitHealth(int* healthUnit) override;
    //~Abyss();
};


#endif //UNTITLED_ABYSS_H
