#include "test.h"
#include "AlgorithmsForShapes.h"


void checkSimiliarRegion()
{
	// ===================== CHECK SIMILIAR REGION ===================== //
	stepik::vector<shared_ptr<Shape>> test1(6);

	test1[0] = shared_ptr<Shape>(new Rectangle({ 0,0 }, 20, 10));
	test1[1] = shared_ptr<Shape>(new    Circle({ 0,0 }, 10));
	test1[2] = shared_ptr<Shape>(new Rectangle({ 0,0 }, 5, 40));
	test1[3] = shared_ptr<Shape>(new Rectangle({ 0,0 }, 40, 5));
	test1[4] = shared_ptr<Shape>(new Rectangle({ 0,0 }, 200, 1));
	test1[5] = shared_ptr<Shape>(new Rectangle({ 0,0 }, 1, 200));

	Region test_r1 = { 0, 3 };
	Region test_r2 = { 2, 5 };

	assert(isSimiliarRegion(test_r1, test_r2, test1) == 0);

	test_r2 = { 1, 4 };
	assert(isSimiliarRegion(test_r1, test_r2, test1) == 1);

	test_r1 = { 2, 4 };
	test_r2 = { 3, 5 };
	assert(isSimiliarRegion(test_r1, test_r2, test1) == 1);

	// ===================== END CHECK SIMILIAR REGION ===================== //
}

void checkSort()
{
	// ============================= CHECK SORT ============================ //
	stepik::vector<shared_ptr<Shape>> test2(8);

	test2[0] = shared_ptr<Shape>(new Circle({ 0,0 }, 6));
	test2[1] = shared_ptr<Shape>(new Circle({ 0,0 }, 5));
	test2[2] = shared_ptr<Shape>(new Circle({ 0,0 }, 4));
	test2[3] = shared_ptr<Shape>(new Circle({ 0,0 }, 3));
	test2[4] = shared_ptr<Shape>(new Circle({ 0,0 }, 2));
	test2[5] = shared_ptr<Shape>(new Circle({ 0,0 }, 1));
	test2[6] = shared_ptr<Shape>(new Circle({ 0,0 }, 0.01));
	test2[7] = shared_ptr<Shape>(new Circle({ 0,0 }, 0.02));

	sortFirstNElements(test2, 3);
	


	assert(fabs((*test2[0]).getSquare() - 0.000314159) <= 0.001);
	assert(fabs((*test2[1]).getSquare() -  0.00125664) <= 0.001);
	assert(fabs((*test2[2]).getSquare() -     3.14159) <= 0.001);
	assert(fabs((*test2[3]).getSquare() -     113.097) <= 0.001);
	assert(fabs((*test2[4]).getSquare() -     78.5398) <= 0.001);
	assert(fabs((*test2[5]).getSquare() -     50.2655) <= 0.001);
	assert(fabs((*test2[6]).getSquare() -     28.2743) <= 0.001);
	assert(fabs((*test2[7]).getSquare() -     12.5664) <= 0.001);

	// ========================= END CHECK SORT ========================== //

	cout << "If you see this, assert tests complete successfully!\n";

}
