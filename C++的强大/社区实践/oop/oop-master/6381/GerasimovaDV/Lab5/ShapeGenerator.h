#ifndef LAB_OOP_2_SHAPEGENERATOR_H
#define LAB_OOP_2_SHAPEGENERATOR_H

#include <random>
#include "vector.h"
#include "shared_ptr.h"
#include "Shape.h"
#include "Parallelogram.h"
#include "Ellipse.h"
#include "EllipseSector.h"

#define CASE_ELLIPSE 0
#define CASE_ELLIPSE_SECTOR 1
#define CASE_PARALLELOGRAM 2

    class ShapeGenerator {
public:
    custom::vector<custom::shared_ptr<Shape>> generate(int num);
    Ellipse* randomEllipse(int id);
    EllipseSector* randomEllipseSector(int id);
    Parallelogram* randomParallelogram(int id);

private:
    float getRandomNumber(int from, int to);
};


#endif //LAB_OOP_2_SHAPEGENERATOR_H
