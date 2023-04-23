
#ifndef OOP_PUDDLE_H
#define OOP_PUDDLE_H

#include "ILandscape.h"

// Puddle -- класс ландшафта лужи.

class Puddle : public ILandscape
{
public:
    void getEffect(Object* object) override;
    char getID() override;
private:
    char id = '~';
};


#endif //OOP_PUDDLE_H
