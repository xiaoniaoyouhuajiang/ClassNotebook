#ifndef LAB_OOP_2_SHAPEALGORITHM_H
#define LAB_OOP_2_SHAPEALGORITHM_H

#include "vector.h"
#include "shared_ptr.h"
#include "Shape.h"
#include "Parallelogram.h"
#include "Ellipse.h"
#include "EllipseSector.h"

class ShapeAlgorithm {
public:
    static bool check_equal(custom::vector<custom::shared_ptr<Shape>>& shapes_first,
                            custom::vector<custom::shared_ptr<Shape>>& shapes_second);
    static int remove_area_greater(custom::vector<custom::shared_ptr<Shape>>& shapes, float max_area);
};


#endif //LAB_OOP_2_SHAPEALGORITHM_H
