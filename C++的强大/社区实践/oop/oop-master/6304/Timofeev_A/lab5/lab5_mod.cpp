#include "figures.h"
#include "shared_ptr.hpp"
#include "vector.hpp"
#include "algs.hpp"
#include "list.hpp"



int main() {

	stepik::vector<stepik::shared_ptr<Shape>> figures(1000);

	GenFigures(figures);

	double criterion = GetCriterion(figures);

	cout << endl << "Criterion: " << criterion << endl << endl;

	int left = 0;
	int right = 0;

	cout << endl << "Swap figure if its perimetr is bigger than criterion " << endl;

	cout << "Enter range borders:" << endl;

	cin >> left >> right;

	stepik::list<stepik::shared_ptr<Shape>> OldFigures = RangeChange(criterion, figures, left, right);

	int count = 0;

	cout << endl << "Old Figures / New Figures:" << endl;
	for (const auto& of : OldFigures) {
		cout << endl << "###############################" << endl;
		cout << endl << "              OLD              " << endl;
		of->operator<<(cout);
		cout << endl << "///////////////////////////////" << endl;
		cout << endl << "              NEW              " << endl;
		figures[left + count]->operator<<(cout);
		count++;
	}

	return 0;
}