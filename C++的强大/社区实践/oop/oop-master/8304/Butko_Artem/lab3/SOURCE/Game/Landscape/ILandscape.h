//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_ILANDSCAPE_H
#define OOP_NEW_ILANDSCAPE_H

#include "../Objects/Object.h"

/*
 * ILandscape -- класс-интерфейс ландшафта.
 */

class ILandscape
{
public:
    virtual void getEffect(Object* object) = 0;
    virtual char getID() = 0;
};


#endif //OOP_NEW_ILANDSCAPE_H
