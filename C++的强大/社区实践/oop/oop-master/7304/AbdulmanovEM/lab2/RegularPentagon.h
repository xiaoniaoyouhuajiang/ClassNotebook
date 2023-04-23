//
// Created by 1 on 21.02.2019.
//

#ifndef SHAPE_REGULARPENTAGON_H
#define SHAPE_REGULARPENTAGON_H

#include <vector>
#include "Shape.h"

class RegularPentagon: public Shape{
public:
    RegularPentagon(Color color,Point center,int lenght);
    void Scale(double coefficient) override;
    friend ostream &operator<<(ostream &out, const RegularPentagon& regularPentagon);

private:
    int lenght;
};
#endif //SHAPE_REGULARPENTAGON_H
