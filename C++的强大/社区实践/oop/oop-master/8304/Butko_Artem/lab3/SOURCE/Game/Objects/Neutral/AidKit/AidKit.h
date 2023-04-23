//
// Created by Artem Butko on 19/05/2020.
//

#ifndef OOP_NEW_AIDKIT_H
#define OOP_NEW_AIDKIT_H

#include "../../../Strategies/AidKitStrategy/Refresh.h"
#include "../INeutral.h"

/* AidKit -- класс нейтрального объекта - аптечка. */

class AidKit : public INeutral
{
public:
    AidKit();
    void getEffect(Object* unit) override;
    void operator>>(Object* unit) override;
};


#endif //OOP_NEW_AIDKIT_H
