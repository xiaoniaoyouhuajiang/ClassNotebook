
#ifndef OOP_ILANDSCAPE_H
#define OOP_ILANDSCAPE_H

#include "../../Unit/Object/Object.h"

/*
 * ILandscape -- класс-интерфейс ландшафта.
 */

class ILandscape
{
public:
    virtual void getEffect(Object* object) = 0;
    virtual char getID() = 0;
};


#endif //OOP_ILANDSCAPE_H
