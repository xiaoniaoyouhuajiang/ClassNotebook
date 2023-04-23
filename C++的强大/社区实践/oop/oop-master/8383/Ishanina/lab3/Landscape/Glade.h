//
// Created by Mila on 15.04.2020.
//

#ifndef UNTITLED_GLADE_H
#define UNTITLED_GLADE_H


#include "Landscape.h"

class Glade: public Landscape {
public:
    Glade();

    char whatYouName() override; //метод для отображения ландшафта на поле как специальной буквы
    LandscapeInterface* copy() override;//метод копирования
    void updateUnitHealth(int* healthUnit) override;
    //~Glade();
};


#endif //UNTITLED_GLADE_H
