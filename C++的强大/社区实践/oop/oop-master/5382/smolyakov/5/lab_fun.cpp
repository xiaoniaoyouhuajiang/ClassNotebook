#include "lab_fun.h"
#include <iostream>

Shape* generateShape() {
  switch (rand()%3) {
  case 0:
    return (new Triangle(RAND_IN_MAX,
                         Point(RAND_IN_MAX, RAND_IN_MAX),
                         Point(RAND_IN_MAX, RAND_IN_MAX)));
  case 1:
    return (new Rhombus(RAND_IN_MAX,
                        RAND_IN_MAX,
                        Point(RAND_IN_MAX, RAND_IN_MAX)));
  case 2:
    return (new Parallelogram(RAND_IN_MAX,
                              RAND_IN_MAX,
                              Point(RAND_IN_MAX, RAND_IN_MAX)));
  }
}

void generateShapes(shapeVec &vec, size_t n) {
  srand(time(NULL));
  for (size_t i = 0; i < n; i++) {
    vec.push_back(
                  stepik::shared_ptr<Shape>
                  (generateShape()));
  }
}

void sortShapeVec(shapeVec &vec) {
  std::sort(vec.begin(), vec.end(),
            [](stepik::shared_ptr<Shape> a,
               stepik::shared_ptr<Shape> b) {
              return (a->area()) < (b->area());
            });
}

bool shapePredicate(const Shape& shape, const Shape& parametr) {
  return parametr.isInsideOfAnother(shape);
}

bool shapePredicate(const Shape& shape) {
  return shapePredicate(shape, DEF_PRED);
}

//Проверка разделен ли диапазон на две группы. Одна группа - фигуры внутри parametr, вторая иначе
bool isPartitioned(const shapeVec& vec, const Shape& parametr) {
  unsigned short ind = 2;
  for (size_t i = 0; i < vec.size()-1; i++) {
    if (!ind)
      return 0;
    if (shapePredicate(*vec[i], parametr) !=
        shapePredicate(*vec[i+1], parametr)) {
      ind--;
    }
  }
  return 1;
}

bool isPartitioned(const shapeVec& vec) {
  return isPartitioned(vec, DEF_PRED);
}

// Создаёт отсортированное пересечение двух массивов
shapeVec intersection(shapeVec& vec1, shapeVec& vec2) {
  shapeVec res;
  sortShapeVec(vec1);
  sortShapeVec(vec2);
  std::set_intersection(vec1.begin(), vec1.end(),
                        vec2.begin(), vec2.end(),
                        std::back_inserter(res),
                        [](stepik::shared_ptr<Shape> a,
                           stepik::shared_ptr<Shape> b) {
                          return (a->area()) < (b->area());
                        });
  return res;
}   

