//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_WATER_H
#define OOP_NEW_WATER_H

#include "../ILandscape.h"

/* Water -- класс ландшафта-воды. */

class Water : public ILandscape
{
public:
    void getEffect(Object* object) override;
    char getID() override;
private:
    char id = '~';
};


#endif //OOP_NEW_WATER_H
