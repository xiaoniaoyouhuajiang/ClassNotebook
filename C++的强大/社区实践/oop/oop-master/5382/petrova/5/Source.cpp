
#include "string"
#include <locale>
#include "Shape.h"
#include "Vector.h"
#include "Shared_ptr.h"
#include "iostream"
#include <algorithm> 
#include <iterator>


using namespace std;

vector<shared_ptr<Shape>> par()
{
	vector<shared_ptr<Shape>> array;
	array.push_back(shared_ptr<Shape>(new Parallelogramm(Point(2.0, -1.0), 6.0, 4.0)));
	array.push_back(shared_ptr<Shape>(new Parallelogramm(Point(2.0, 1.0), 9.0, 11.0)));
	return array;
}

vector<shared_ptr<Shape>> ellips()
{
	vector<shared_ptr<Shape>> array;
	array.push_back(shared_ptr<Shape>(new Ellips(Point(10.0, -10.0), 5, 3)));
	array.push_back(shared_ptr<Shape>(new Ellips(Point(6.0, 8.0), 1, 9)));

	return  array;
}

vector<shared_ptr<Shape>> segel()
{
	vector<shared_ptr<Shape>> array;
	array.push_back(shared_ptr<Shape>(new SegEl(Point(0.0, 0), Point(3.0, 2.0), Point(4.0, 3.0))));
	array.push_back(shared_ptr<Shape>(new SegEl(Point(9.0, 5.0), Point(9.0, 2.0), Point(6.0, 3.0))));
	return array;
}


bool predicate1(const shared_ptr<Shape> &a) {
	Parallelogramm par1(Point(2.0, -1.0), 6.0, 4.0);
	return par1.equalProjection(*a, X);
}

bool predicate2(const shared_ptr<Shape> &a) {
	Ellips ellipse(Point(10.0, -10.0), 5, 3);
	return ellipse.equalProjection(*a, X);
}
bool predicate3(const shared_ptr<Shape> &a) {
	SegEl seg1(Point(0.0, 0.0), Point(1.0, 2.0), Point(3.0, 3.0));
	return seg1.equalProjection(*a, X);
}


TEST(tests1, test_par) {
	vector<shared_ptr<Shape>> first = par();
	EXPECT_TRUE(std::is_permutation(first.begin(), first.end(), predicate1));
}
TEST(tests1, test_ellips) {
	vector<shared_ptr<Shape>> first = ellips ();
	EXPECT_TRUE(std::is_permutation(first.begin(), first.end(), predicate2));
}
TEST(tests1, tests_segellips) {
	vector<shared_ptr<Shape>> first = segel();
	EXPECT_FALSE(std::is_permutation(first.begin(), first.end(), predicate3));
}

GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	srand(time(0));
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}  