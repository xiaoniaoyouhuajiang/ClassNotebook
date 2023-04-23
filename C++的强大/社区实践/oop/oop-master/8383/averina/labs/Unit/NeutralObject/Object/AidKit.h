#ifndef OOP_AIDKIT_H
#define OOP_AIDKIT_H


#include "../../Object/Object.h"
#include "INeutral.h"

/* AidKit -- класс нейтрального объекта - аптечка. */

class AidKit : public INeutral
{
public:
    AidKit();
    void getEffect(Object* unit) override;
    // перегрузка оператора
    void operator>>(Object* unit) override;
};

#endif //OOP_AIDKIT_H
