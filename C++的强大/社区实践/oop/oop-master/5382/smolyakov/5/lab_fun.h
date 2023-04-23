#include "vector.h"
#include "shared_ptr.cpp"
#include "figure.h"
#define MAX_VALUE 50
#define RAND_IN_MAX rand()%MAX_VALUE+1
#define DEF_PRED (Parallelogram(100, 100, Point(-50, -50))) 

using namespace stepik;

typedef stepik::vector<stepik::shared_ptr<Shape>> shapeVec;

Shape* generateShape();

void generateShapes(shapeVec &vec, size_t n = 1000);

void sortShapeVec(shapeVec &vec); 

//Проверка разделен ли диапазон на две группы. Одна группа - фигуры внутри parametr, вторая иначе
bool isPartitioned(const shapeVec& vec, const Shape& parametr);

bool isPartitioned(const shapeVec& vec);

// Создаёт отсортированное пересечение двух массивов
shapeVec intersection(shapeVec& vec1, shapeVec& vec2);


bool shapePredicate(const Shape& shape, const Shape& parametr);

bool shapePredicate(const Shape& shape);
