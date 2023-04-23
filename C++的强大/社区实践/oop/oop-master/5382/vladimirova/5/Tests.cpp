// OOP_LR5_Olya.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "Shape.h"
#include "List.h"
#include "Shared_ptr.h"
#include <ctime>
#include <algorithm>
#include "gtest/gtest.h"

const float diapazon = 10;

float fRand(float fMin = -diapazon, float fMax = diapazon)
{
	float f = (float)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

list<shared_ptr<Shape>> create_figures(bool make_container_of_figures_from_small_diapazon = false) {

	list<shared_ptr<Shape>> tmp;
	if (make_container_of_figures_from_small_diapazon) {
		for (size_t i = 0; i < 1000; ++i) {
			static size_t x;
			x = rand() % 3;
			switch (x) {
			case 0: {
				tmp.push_back(shared_ptr<Shape>
				(new Ellipse_m(fRand(-0.5 * diapazon, 0.5 * diapazon), fRand(-0.5 * diapazon, 0.5 * diapazon),
					"black", fRand(diapazon, 2 * diapazon), fRand(diapazon, 2 * diapazon))));
				break;
			}
			case 1: {
				tmp.push_back(shared_ptr<Shape>
				(new Sector(fRand(-0.5 * diapazon, 0.5 * diapazon), fRand(-0.5 * diapazon, 0.5 * diapazon),
					"white", fRand(diapazon, 2 * diapazon), fRand(diapazon, 2 * diapazon), rand(), rand())));
				break;
			}
			case 2: {
				tmp.push_back(shared_ptr<Shape>
				(new Parallelogram(fRand(-0.5 * diapazon, 0.5 * diapazon), fRand(-0.5 * diapazon, 0.5 * diapazon),
					"blue", fRand(diapazon, 2 * diapazon), fRand(diapazon, 2 * diapazon), rand())));
				break;
			}
			}
		}
	}
	else {
		for (size_t i = 0; i < 1000; ++i) {
			static size_t x;
			x = rand() % 3;
			switch (x) {
			case 0: {
				tmp.push_back(shared_ptr<Shape>
				(new Ellipse_m(fRand(), fRand(), "black", fRand(0, diapazon), fRand(0, diapazon))));
				break;
			}
			case 1: {
				tmp.push_back(shared_ptr<Shape>
				(new Sector(fRand(), fRand(), "white", fRand(0, diapazon), fRand(0, diapazon), rand(), rand())));
				break;
			}
			case 2: {
				tmp.push_back(shared_ptr<Shape>
				(new Parallelogram(fRand(), fRand(), "blue", fRand(0, diapazon), fRand(0, diapazon), rand())));
				break;
			}
			}
		}
	}
	
	return tmp;
}

bool binary_predicate(const shared_ptr<Shape> &a, const shared_ptr<Shape> &b) {
	return isIntersect(*a, *b);
}

bool unary_predicate(const shared_ptr<Shape> &a) {
	Parallelogram parallelogram(0, 0, "black", 10, 10, 90);
	return isIntersect(parallelogram, *a);
}

TEST(Algorithm_tests, not_equal) {
	list<shared_ptr<Shape>> first = create_figures();
	list<shared_ptr<Shape>> second = create_figures();
	EXPECT_FALSE(std::is_permutation(first.begin(), first.end(), second.begin(), binary_predicate));
}

TEST(Algorithm_tests, equal) {
	list<shared_ptr<Shape>> first = create_figures(true);
	list<shared_ptr<Shape>> second;
	for (size_t i = 0; i < 1000; ++i)
		second.push_back(shared_ptr<Shape>(new Parallelogram(0, 0, "white", 10, 10, 90)));
	EXPECT_TRUE(std::is_permutation(first.begin(), first.end(), second.begin(), binary_predicate));
}

TEST(Algorithm_tests, remove) { 
	list<shared_ptr<Shape>> collection = create_figures();
	list<shared_ptr<Shape>>::iterator end = std::remove_if(collection.begin(), collection.end(), unary_predicate);
	for (auto it = collection.begin(); it != end; ++it)
		EXPECT_FALSE(unary_predicate(*it));
}

GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	srand(time(0));
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	return 0;
}
