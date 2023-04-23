#include <algorithm> 
#include "shape.h"
#include "list.h"
#include "Shared_ptr.h"
#include <functional>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

const double diapason = 10;

double rand_val(double fMin = -diapason, double fMax = diapason)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

list<shared_ptr<Shape>> creator() {
	list<shared_ptr<Shape>> tmp;
	for (size_t i = 0; i < 1000; ++i) {
		static size_t x;
		x = rand() % 3;

		switch (x) {

		case 0: {
			tmp.push_back(shared_ptr<Shape>
				(new Rectangle(Point(rand_val(), rand_val()), rand_val(0), 1, rand_val(), rand_val())));
			break;
		}

		case 1: {
			vector <Point> vec = { Point(rand_val(), rand_val()),
				Point(rand_val(), rand_val()), Point(rand_val(), rand_val()),
				Point(rand_val(), rand_val()), Point(rand_val(), rand_val()) };
			tmp.push_back(shared_ptr<Shape>
				(new Pentagon(Point(rand_val(), rand_val()), rand_val(0), 1, vec)));
			break;
		}

		case 2: {
			tmp.push_back(shared_ptr<Shape>
				(new Star(Point(rand_val(), rand_val()), rand_val(0), 1, rand_val(0))));
			break;
		}
		}
	}
	return tmp;
}

bool unary_predicate(const shared_ptr<Shape>& array, Rectangle shape_etalon) {
	return shape_etalon.common_vertex(*array);
}

TEST(Algorithm_tests, Non_modifying_test_true)
{
	list<shared_ptr<Shape>> array = creator();
	Rectangle shape_etalon(Point(1, 1), 1, 1, 1, 1);
	array.push_back(shared_ptr<Shape>
		(new Rectangle(Point(1, 1), 1, 1, 1, 1)));
	using namespace std::placeholders;
	EXPECT_TRUE(std::any_of(array.begin(), array.end(), std::bind(&unary_predicate, _1, shape_etalon)));
}

TEST(Algorithm_tests, Non_modifying_test_false)
{
	list<shared_ptr<Shape>> array = creator();
	Rectangle shape_etalon(Point(10 * diapason, 10 * diapason), rand_val(), 1, rand_val(0), rand_val(0));
	using namespace std::placeholders;
	EXPECT_False(std::none_of(array.begin(), array.end(), std::bind(&unary_predicate, _1, shape_etalon)));
}

TEST(Algorithm_tests, Modifying_test_true)
{
	list<shared_ptr<Shape>> array_1 = creator();
	Rectangle shape_etalon(Point(1, 1), 1, 1, 1, 1);
	array_1.push_back(shared_ptr<Shape>
		(new Rectangle(Point(1, 1), 1, 1, 1, 1)));
	using namespace std::placeholders;
	list<shared_ptr<Shape>> array_2 = std::unique_copy(array_1.begin(), array_1.end(), array_2.begin(),
		std::bind(&unary_predicate, _1, shape_etalon));
	
	EXPECT_TRUE(array_2.size() < array_1.size());
}

GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}
