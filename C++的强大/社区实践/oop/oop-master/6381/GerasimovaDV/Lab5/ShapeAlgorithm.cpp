#include "ShapeAlgorithm.h"

bool ShapeAlgorithm::check_equal(custom::vector<custom::shared_ptr<Shape>>& shapes_first,
                 custom::vector<custom::shared_ptr<Shape>>& shapes_second) {
    float sum_first = 0;
    float sum_second = 0;
    for(auto elem : shapes_first) {
        sum_first += elem->area();
    }
    for(auto elem : shapes_second) {
        sum_second += elem->area();
    }
    return sum_first == sum_second;
}

int ShapeAlgorithm::remove_area_greater(custom::vector<custom::shared_ptr<Shape>>& shapes, float max_area) {
    int counter = 0;
    for(int i = 0; i < shapes.size(); i++) {
        if(shapes[i]->area() > max_area) {
            shapes.erase(&shapes[i]);
            counter++;
            i--;
        }
    }
    return counter;
}