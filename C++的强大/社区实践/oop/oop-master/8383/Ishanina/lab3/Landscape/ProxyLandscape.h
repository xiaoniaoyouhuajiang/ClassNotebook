//
// Created by Mila
//

#ifndef UNTITLED_PROXYLANDSCAPE_H
#define UNTITLED_PROXYLANDSCAPE_H


#include "Landscape.h"

class ProxyLandscape: public Landscape {
public:
    explicit ProxyLandscape(Landscape* landscape);
    char whatYouName() override; //метод для отображения ландшафта на поле как специальной буквы
    LandscapeInterface* copy() override;//метод копирования
    void updateUnitHealth(int* healthUnit) override;

private:
    Landscape* landscape;

};


#endif //UNTITLED_PROXYLANDSCAPE_H
