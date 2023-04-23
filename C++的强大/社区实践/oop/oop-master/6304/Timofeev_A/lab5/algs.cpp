#include "algs.hpp"

void GenFigures(stepik::vector<stepik::shared_ptr<Shape>>& FigureVector) { //creating a vector of 1000 elements
	for (unsigned int i = 0; i < FigureVector.size(); ++i) {
		int k = rand() % 3;
		if (!k)
			FigureVector[i] = stepik::shared_ptr<Shape>(new Pentagon(rand() % 5, rand() % 5, 1 + rand() % 5));
		else if (k == 1)
			FigureVector[i] = stepik::shared_ptr<Shape>(new Pentagram(rand() % 5, rand() % 5, 1 + rand() % 5));
		else
			FigureVector[i] = stepik::shared_ptr<Shape>(new Rectangle(rand() % 4, rand() % 4, 1 + rand() % 4, 1 + rand() % 4));
	}
}

double GetCriterion(stepik::vector<stepik::shared_ptr<Shape>>& FigureVector) {
	double criterion = 0;
	for (const auto& figure : FigureVector) {
		criterion += figure->GetPerimetr();
	}

	return criterion / FigureVector.size();
}

bool CriterionCheck(double criterion, stepik::vector<stepik::shared_ptr<Shape>>& FigureVector, int left, int right) {
	for (int i = left - 1; i < right; ++i) {
		if (FigureVector[i]->GetPerimetr() > criterion) {
			return true;
		}
	}

	return false;
}

stepik::list<stepik::shared_ptr<Shape>> RangeChange(double criterion, stepik::vector<stepik::shared_ptr<Shape>>& FigureVector, int left, int right) {

	stepik::vector<stepik::shared_ptr<Shape>> RandomNewFigures(right - left + 1);

	GenFigures(RandomNewFigures);

	stepik::list<stepik::shared_ptr<Shape>> CopiedFigures;

	for (int i = left - 1; i < right; ++i) {
		CopiedFigures.push_back(FigureVector[i]);
		if (FigureVector[i]->GetPerimetr() > criterion) {
			FigureVector[i].swap(RandomNewFigures[i - left + 1]);
		}
	}

	return CopiedFigures;
}