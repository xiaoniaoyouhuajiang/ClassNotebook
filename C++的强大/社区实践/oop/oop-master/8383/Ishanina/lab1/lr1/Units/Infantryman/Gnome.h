//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_GNOME_H
#define UNTITLED_GNOME_H


#include "Infantryman.h"

class Gnome: public Infantryman {
public:
    Gnome();
    void whatYouName() override;
    ObjectInterface* copy() override;
};


#endif //UNTITLED_GNOME_H
