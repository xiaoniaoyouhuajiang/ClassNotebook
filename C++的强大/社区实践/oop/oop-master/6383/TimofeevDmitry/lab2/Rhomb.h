// Timofeev Dmitry № 17 var 6
// Треугольник, ромб, параллелограмм

#ifndef LAB2_FIGURES_H
#define LAB2_FIGURES_H

#include <vector>
#include "Parallelogram.h"

class Rhomb: public Parallelogram{
public:
    // по двум диагоналям
    Rhomb(std::string color,double width, double height);
    std::string toString() const override;
};
#endif //LAB2_FIGURES_H