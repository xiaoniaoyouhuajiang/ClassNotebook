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

	cout << endl << "If there is figure that satisfies the parameter" << endl;

	cout << "Enter range borders:" << endl;

	cin >> left >> right;

    bool res = CriterionCheck(criterion, figures, left, right);
    
    if (res) {
        cout << endl << "There is figure that satisfies the parameter!" << endl;
    } else {
        cout << endl << "There is no figure that satisfies the parameter!" << endl;
    }

	return 0;
}