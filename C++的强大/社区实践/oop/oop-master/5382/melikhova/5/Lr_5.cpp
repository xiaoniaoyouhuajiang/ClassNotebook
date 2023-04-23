// Lr_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include "vector.h"
#include "shared_ptr.h"
#include "Shape.h"
#include "gtest/gtest.h"
#include <functional>

using namespace std;

const float diapason = 10;

float random(float fMin = -diapason, float fMax = diapason)
 {
	float f = (float)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
	}

my_vector<shared_ptr<Shape>> creator() {
	my_vector<shared_ptr<Shape>> tmp;
	for (size_t i = 0; i < 1000; ++i) {
		static size_t x;
		x = rand() % 3;

		switch (x) {

			case 0: {
				tmp.push_back ( shared_ptr<Shape>
					(new Circle(static_cast<Colour>(rand() % 6), Point(random(), random()), random(0))));
						break;
						}

			case 1: {
				tmp.push_back(shared_ptr<Shape>
					(new Pentagon(static_cast<Colour>(rand() % 6), Point(random(), random()), random(0))));
					break;
					}

			case 2: {
					tmp.push_back(shared_ptr<Shape>
						(new Wrong_Pentagon(static_cast<Colour>(rand() % 6), Point(random(), random()),
							Point(random(), random()), Point(random(), random()),
							Point(random(), random()), Point(random(), random()))));
					break;
				}		
		}		
	}
	return tmp;
}

bool binary_predicate(const shared_ptr<Shape> &array_1, const shared_ptr<Shape> &array_2, Circle etalon_shape) {
	return (etalon_shape.is_perimeter_bigger(*array_1) == etalon_shape.is_perimeter_bigger(*array_2));
}

TEST(Algorithm_tests, Non_modifying_test_true)
{
	my_vector<shared_ptr<Shape>> array_1 = creator();
	std::sort(array_1.begin(), array_1.end());
	my_vector<shared_ptr<Shape>> array_2 = creator();
	std::sort(array_2.begin(), array_2.end());
	Circle etalon_shape(static_cast<Colour>(rand() % 6), Point(random(), random()), 1000 * random(0));
	using namespace std::placeholders;
	EXPECT_TRUE(std::equal(array_1.begin(), array_1.end(), array_2.begin(), std::bind(&binary_predicate, _1, _2, etalon_shape)));
}

TEST(Algorithm_tests, Non_modifying_test_false)
{
	my_vector<shared_ptr<Shape>> array_1 = creator();
	std::sort(array_1.begin(), array_1.end());
	my_vector<shared_ptr<Shape>> array_2 = creator();
	std::sort(array_2.begin(), array_2.end());
	Circle etalon_shape(static_cast<Colour>(rand() % 6), Point(random(), random()), random(0));
	using namespace std::placeholders;
	EXPECT_FALSE(std::equal(array_1.begin(), array_1.end(), array_2.begin(), std::bind(&binary_predicate, _1, _2, etalon_shape)));
}

TEST(Algorithm_tests, Modifying_test_true)
{
	my_vector<shared_ptr<Shape>> array_1 = creator();
	int n = rand()%1000;
	std::partial_sort(array_1.begin(), array_1.begin() + n, array_1.end());
	for (auto i = array_1.begin(); i < array_1.begin() + n - 1;) {
		EXPECT_TRUE(*i <= *(++i));
	}
}

GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}