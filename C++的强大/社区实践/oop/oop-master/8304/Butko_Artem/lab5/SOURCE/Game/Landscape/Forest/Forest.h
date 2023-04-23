//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_FOREST_H
#define OOP_NEW_FOREST_H


#include "../ILandscape.h"

/* Forest -- класс ландшафта-леса. */

class Forest : public ILandscape
{
public:
    void getEffect(Object* object) override;
    char getID() override;
private:
    char id = '$';
};


#endif //OOP_NEW_FOREST_H
