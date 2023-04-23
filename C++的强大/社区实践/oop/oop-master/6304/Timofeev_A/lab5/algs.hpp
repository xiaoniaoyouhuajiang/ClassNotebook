#ifndef ALGS_HPP
#define ALGS_HPP

#include "figures.h"
#include "shared_ptr.hpp"
#include "vector.hpp"
#include "list.hpp"


void GenFigures(stepik::vector<stepik::shared_ptr<Shape>>& FigureVector);
double GetCriterion(stepik::vector<stepik::shared_ptr<Shape>>& FigureVector);

bool CriterionCheck(double criterion, stepik::vector<stepik::shared_ptr<Shape>>& FigureVector, int left, int right);

stepik::list<stepik::shared_ptr<Shape>> RangeChange(double criterion, stepik::vector<stepik::shared_ptr<Shape>>& FigureVector, int left, int right);




#endif // !ALGS_HPP
