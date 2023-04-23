#include <ctime>
#include "test.h"
#include "AlgorithmsForShapes.h"


int main()
{
	checkSimiliarRegion();
	checkSort();
	stepik::vector<shared_ptr<Shape>> a = generateFigures(1000);
	
	Region r1 = { 0, 100 };
	Region r2 = { 100, 200 };

	printVector(a);
	cout << "is Similiar regions: " << isSimiliarRegion(r1, r2, a);

	sortFirstNElements(a, 500);
	cout << "Sort Complete\n\n";
	printVector(a);

	return 0;
}

