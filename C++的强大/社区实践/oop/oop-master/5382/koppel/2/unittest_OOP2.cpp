#include "gtest\gtest.h"
#include "ConsoleApplication2\stdafx.h"
#include "ConsoleApplication2\pentagon.h"
#include "ConsoleApplication2\point.h"
#include "ConsoleApplication2\rectangle.h"
#include "ConsoleApplication2\shape.h"
#include "ConsoleApplication2\star.h"
#include <vector>

using namespace std;
//1. Два прямоугольника, имеющие обшие вершины
TEST(area_test, double_rectangle_true) {
	Point center_first(2, 2);
	Point center_second(0, 0);

	Rectangle first(center_first, 0, 0, 2, 2);
	Rectangle second(center_second, 0, 0, 2, 2);

	ASSERT_EQ(true, first.common_vertex(second));
}


TEST(area_test, double_rectangle_false)
{//2. Два прямоугольника, не имеющие общие вершины
	Point center_first(3, 3);
	Point center_second(0, 0);

	Rectangle first(center_first, 0, 0, 2, 2);
	Rectangle second(center_second, 0, 0, 2, 2);

	ASSERT_EQ(false, first.common_vertex(second));
}

TEST(area_test, double_pentagon_true)
{//3. Пятиугольники, имеющие общие вершины
	vector <Point> first_vec{ Point(5, 1), Point(1, 4), Point(0, 3), Point(4, 5), Point(3, 0) };
	vector <Point> second_vec{ Point(-2, 2), Point(0, 3), Point(-2, -2), Point(2, -2), Point(2, 0) };
	Point center_first(2, 2);
	Point center_second(0, 0);
	Pentagon first(center_first, 0, 0, first_vec);
	Pentagon second(center_second, 0, 0, second_vec);

	ASSERT_EQ(true, first.common_vertex(second));
}

TEST(area_test, double_pentagon_false)
{//4. Пятиугольники, не имеющие общие вершины
	Point center_first(3, 3);
	Point center_second(-3, -3);

	vector <Point> first_vec{ Point(5, 1), Point(1, 4), Point(0, 3), Point(4, 5), Point(3, 0)};
	vector <Point> second_vec{ Point(-3, 0), Point(-1, -3), Point(-1, -4), Point(-5, -1), Point(-4, -5)};
	Pentagon first(center_first, 0, 0, first_vec);
	Pentagon second(center_second, 0, 0, second_vec);

	ASSERT_EQ(true, first.common_vertex(second));
}

TEST(area_test, rectangle_pentagon_false)
{//5. Прямоугольник и пятиугольник - ne имеют
	Point center_first(2.5, 2.5);
	Point center_second(3, 3);
	vector <Point> second_vec{ Point(5, 1), Point(1, 4), Point(0, 3), Point(4, 5), Point(3, 0) };
	
	Rectangle first(center_first, 0, 0, 3.5, 2.5);
	Pentagon second(center_second, 0, 0, second_vec);

	ASSERT_EQ(false, first.common_vertex(second));
}

TEST(area_test, rectangle_pentagon_true)
{//6. Прямоугольник и пятиугольник - имеют
	Point center_first(-3, -3);
	Point center_second(3, 3);
	vector <Point> second_vec{ Point(5, 1), Point(1, 4), Point(0, 3), Point(4, 5), Point(3, 0) };

	Rectangle first(center_first, 0, 0, 6, 6);
	Pentagon second(center_second, 0, 0, second_vec);

	ASSERT_EQ(true, first.common_vertex(second));
}

GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	return 0;
}