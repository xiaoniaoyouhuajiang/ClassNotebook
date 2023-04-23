#ifndef LONCHINA_LIBRARY_H
#define LONCHINA_LIBRARY_H

#include "../Figures/AbstractShape.h"
#include "../Figures/Point.h"

#include <vector>
#include <string>
#include <iostream>

// сокращаем повторяющийся код в createShape
// vector<Point> & coord вектор координат фигуры
// Point & center координаты центра
// int dots количество точек
// string figure название фигуры
void create(std::vector<Point> & coord, Point & center, int dots, std::string figure);

//bool compareFigures(const AbstractShape& first, const AbstractShape& second);

#endif //LONCHINA_LIBRARY_H
