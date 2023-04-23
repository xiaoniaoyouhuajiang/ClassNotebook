#pragma once

#include "stdafx.h"
#include "List.h"
#include "Shapes.h"
#include "Shared_ptr.h"
#include "gtest/gtest.h"
#include <iostream>
#include <ctime>

const size_t definite_square = 15;

bool binary_pred(const shared_ptr<Shape> &a, const shared_ptr<Shape> &b) {
	return b->check(*a, *b);
}

bool unary_pred(const shared_ptr<Shape> &a) {
	return a->square() > definite_square;
}

my_list<shared_ptr<Shape>> generate_objects() {

	my_list<shared_ptr<Shape>> list;
	for (size_t i = 0; i < 1000; ++i) {
		static size_t x;
		x = rand() % 3;
		switch (x) {
		case 0: {
			list.push_back(shared_ptr<Shape>(new Rectangle(rand() % 7 + 1, rand() % 7 + 1, rand() % 10 - 5, rand() % 10 - 5, 0, "white")));
			break;
		}
		case 1: {
			list.push_back(shared_ptr<Shape>(new Square(rand() % 7 + 1, rand() % 10 - 5, rand() % 10 - 5, 0, "white")));
			break;

		}
		case 2: {
			list.push_back(shared_ptr<Shape>(new Ellipse(rand() % 7 + 1, rand() % 7 + 1, rand() % 10 - 5, rand() % 10 - 5, 0, "white")));
			break;
		}
		}
	}
	return list;
}

TEST(Algorithm_tests, Non_modifying)
{
	my_list<shared_ptr<Shape>> list = generate_objects();
	shared_ptr<Shape> temp(new Ellipse(4,2,0,0));
	size_t count = 2;
	auto it = search_n(list.begin(), list.end(), count, temp, binary_pred);
	if (it != list.end()) for (size_t i = 0; i != count; ++i, ++it){
		EXPECT_TRUE(temp->check(*temp, *(it->get())));
	}
}

TEST(Algorithm_tests, Modifying){
	my_list<shared_ptr<Shape>> list = generate_objects();
	my_list<shared_ptr<Shape>>::iterator end = remove_if(list.begin(), list.end(), unary_pred);
	for (auto it = list.begin(); it != end; ++it) EXPECT_FALSE(unary_pred(*it));
}

GTEST_API_ int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

