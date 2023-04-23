//
// Created by Mila
//

#ifndef UNTITLED_LANDSCAPEINTERFACE_H
#define UNTITLED_LANDSCAPEINTERFACE_H

class LandscapeInterface{
public:

    virtual char whatYouName() = 0; //метод для отображения ландшафта на поле как специальной буквы
    virtual LandscapeInterface* copy() = 0;//метод копирования
    virtual void updateUnitHealth(int* healthUnit, char nameUnit) = 0;//

};

#endif //UNTITLED_LANDSCAPEINTERFACE_H
