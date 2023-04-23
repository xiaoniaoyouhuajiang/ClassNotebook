//
// Created by Максим Бачинский on 27.03.17.
//

#ifndef OOPFIGURES_REGULARPENTANGLE_H
#define OOPFIGURES_REGULARPENTANGLE_H


#include "Pentangle.h"

class RegularPentangle : public Pentangle {
private:
    double radius;
public:
    RegularPentangle(const Point &center, const Point &point, const Color &color);

    double getRadius() const;

};


#endif //OOPFIGURES_REGULARPENTANGLE_H
