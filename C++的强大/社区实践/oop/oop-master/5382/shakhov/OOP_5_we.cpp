// OOP_5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <algorithm> 
#include <iterator>
#include "Shape.h"
#include "Vector.h"
#include "Shared_ptr.h"
#include "gtest/gtest.h"

const size_t definite_square = 200;

bool binary_pred(const shared_ptr<Shape> &a, const shared_ptr<Shape> &b) {
	return b.get()->isInsideOfAnother(*(a.get()));
}

bool unary_pred(const shared_ptr<Shape> &a) {
	return a.get()->square() > definite_square;
}

my_vector<shared_ptr<Shape>> generate_objects() {

	my_vector<shared_ptr<Shape>> array;
	for (size_t i = 0; i < 1000; ++i) {
		static size_t x;
		x = rand() % 3;
		switch (x) {
		case 0: {
			array.push_back(shared_ptr<Shape>(new Square));
			break;
		}
		case 1: {
			array.push_back(shared_ptr<Shape>(new Rectangle));
			break;
		}
		case 2: {
			array.push_back(shared_ptr<Shape>(new Ellipse));
			break;
		}
		}
	}
	return array;
}

TEST(Algorithm_tests, Non_modifying)
{
	my_vector<shared_ptr<Shape>> array = generate_objects();

	shared_ptr<Shape> check(new Ellipse(Point(0, 0), Point(1, 0), Point(0, 1)));
		
	EXPECT_FALSE(none_of(array.begin(), array.end(), unary_pred)); //пороговые значения definite_square
}

TEST(Algorithm_tests, Modifying)
{
	my_vector<shared_ptr<Shape>> array = generate_objects();

	my_vector<shared_ptr<Shape>> result(array.size());

	remove_copy_if(array.begin(), array.end(), 
		stdext::make_unchecked_array_iterator(result.begin()), 
		unary_pred);

	auto it = result.begin();
	for (; ((it->get() != nullptr) && (it != result.end())); ++it);
	result.resize(it - result.begin());

	for (it = result.begin(); it != result.end(); ++it) {
		EXPECT_FALSE(it->get()->square() > definite_square);
	}
}



GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	srand(time(0));
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	return 0;
}