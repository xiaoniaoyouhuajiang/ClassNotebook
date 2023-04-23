//
// Created by Mila
//

#ifndef UNTITLED_LANDSCAPE_H
#define UNTITLED_LANDSCAPE_H


#include "LandscapeInterface.h"

class Landscape: public LandscapeInterface {
protected:
    char name;
public:
    char whatYouName() override = 0; //метод для отображения ландшафта на поле как специальной буквы
    LandscapeInterface* copy() override = 0;//метод копирования
    void updateUnitHealth(int* healthUnit) override = 0;

};


#endif //UNTITLED_LANDSCAPE_H
