#include "string"
#include <locale>
#include "Shape.h"
#include "Pentagon.h"
#include "Segment.h"
#include "Ellips.h"
#include "Vector.h"
#include "Shared_ptr.h"
#include "iostream"
#include <algorithm> 
#include <iterator>


using namespace std;

vector<shared_ptr<Shape>> pen()
{
	vector<shared_ptr<Shape>> array;
	array.push_back(shared_ptr<Shape>(new Pentagon(0, 0, 3, 4.0, 45, "pink")));
	array.push_back(shared_ptr<Shape>(new Pentagon(2, 3, 3, 5.0, 45, "black")));
	return array;
}

vector<shared_ptr<Shape>> ellips()
{
	vector<shared_ptr<Shape>> array;
	array.push_back(shared_ptr<Shape>(new Ellips(0, 3, 7, 8, 3.0, 90, "pink")));
	array.push_back(shared_ptr<Shape>(new Ellips(0, 3, 3, 4, 3.0, 90, "blue")));

	return  array;
}

vector<shared_ptr<Shape>> segment()
{
	vector<shared_ptr<Shape>> array;
	array.push_back(shared_ptr<Shape>(new Segment(0, 0, 3, 2.0, 60, "yellow")));
	array.push_back(shared_ptr<Shape>(new Segment(1, 1, 3, 2.0, 60, "red")));
	return array;
}


bool predicate1(const shared_ptr<Shape> &a) {
	Pentagon pen1(0, 0, 3, 4.0, 45, "pink");
	return pen1.equalProjection(*a);
}

bool predicate2(const shared_ptr<Shape> &a) {
	Ellips ellipse(0, 3, 7, 8, 3.0, 90, "pink");
	return ellipse.equalProjection(*a);
}
bool predicate3(const shared_ptr<Shape> &a) {
	Segment seg1(0, 0, 3, 2.0, 60, "yellow");
	return seg1.equalProjection(*a);
}


TEST(tests1, test_pen) {
	vector<shared_ptr<Shape>> first = pen();
	EXPECT_TRUE(std::none_of(first.begin(), first.end(), predicate1));
}
TEST(tests1, test_ellips) {
	vector<shared_ptr<Shape>> first = ellips();
	EXPECT_TRUE(std::none_of(first.begin(), first.end(), predicate2));
}
TEST(tests1, tests_segment) {
	vector<shared_ptr<Shape>> first = segment();
	EXPECT_FALSE(std::none_of(first.begin(), first.end(), predicate3));
}



GTEST_API_ int main(int argc, char **argv) {

	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}