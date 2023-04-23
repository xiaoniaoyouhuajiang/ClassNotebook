//
// Created by olyaave on 31.05.2020.
//

#ifndef OOP_MOUNTAIN_H
#define OOP_MOUNTAIN_H

#include "ILandscape.h"

/* Mountain -- класс ландшафта-горы. */

class Mountain : public ILandscape
{
public:
    void getEffect(Object* object) override;
    char getID() override;
private:
    char id = '^';
};



#endif //OOP_MOUNTAIN_H
