#include <gtest\gtest.h>
#include <generator.h>
#include <alg.h>
TEST(Figure_Tests, SameShape)
{
	
	RightTriangle testShape( { Point(0, 0), Point(4, 0), Point(0, 4) });
	RightTriangle sh1({ Point(0, 4), Point(0, 0), Point(4, 0) });
	RightTriangle sh2({ Point(4, 4), Point(4, 5), Point(5, 4) });

	EXPECT_EQ(false, testShape.similar(sh1, sh2));
}

TEST(Figure_Tests, RTriangle_SquareRightTInside)
{
	
	RightTriangle testShape({ Point(0, 0), Point(4, 0), Point(0, 4) });
	Square sh1({ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	RightTriangle sh2({ Point(0, 4), Point(4, 0), Point(4, 4) });
	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(Figure_Tests, RTriangle_SquareRightOutsideP)
{
	
	RightTriangle testShape({ Point(0, 0), Point(4, 0), Point(0, 4) });
	Square sh1({ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	RightTriangle sh2({ Point(-1, 5), Point(4, 0), Point(4, 5) });
	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(Figure_Tests, RTriangle_RTriangle_SquareRightOutsideP)
{
	
	RightTriangle testShape({ Point(0, 0), Point(4, 0), Point(0, 4) });
	Square sh1( {Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	IsoscelesTriangle sh2({ Point(4, 0), Point(4, 8), Point(4, 4) });

	EXPECT_EQ(true, testShape.similar(sh1, sh2));
}
TEST(SquareCenter, center)
{
	Square sh1({ Point(0, 0), Point(4, 0), Point(0, 4), Point(4, 4) });
	Point testp(sh1.findCenter());

	EXPECT_TRUE(testp == Point(2, 2));


}
TEST(Vector_Tests, input)
{
	stepik::vector<int> test;
	test.push_back(5);
	test.push_back(777);

	EXPECT_EQ(5, test[0]);
}
TEST(Vector_Tests, deleteT)
{
	stepik::vector<int> test{5,777};
	test.erase(test.begin());
	EXPECT_EQ(777,test[0]);
}
TEST(Shared_Test, result)
{
	stepik::shared_ptr<int> test(new int (777));
	EXPECT_EQ(777,*test );
	
}

TEST(alg_Test, random_non_mod)
{
	long int MAX = 1000;//max count Shape.
	long int diapazoneLimit = 80;//for odds insrease.
	stepik::vector<stepik::shared_ptr<Shape>> ShapeArray = generate_shape_array(MAX,diapazoneLimit);
	stepik::shared_ptr<Point> testP(new Point(30, 30));
	size_t count = 1;
	auto result=std::search_n(ShapeArray.begin(), ShapeArray.end(),count, *testP,pred_two);
	for (int q=0;q<result->use_count();++q)
	EXPECT_TRUE (result->get()->insidePoint(*testP));
}

TEST(alg_Test, random_mod)
{
	long int MAX = 1000;//max count Shape.
	long int diapazoneLimit = 80;//for odds insrease.
	stepik::vector<stepik::shared_ptr<Shape>>ShapeArray = generate_shape_array(MAX, diapazoneLimit);
	stepik::vector<stepik::shared_ptr<Shape>> trueReuslt(MAX);
	stepik::vector<stepik::shared_ptr<Shape>> falseResult(MAX);
	std::copy_if(ShapeArray.begin(), ShapeArray.end(), trueReuslt.begin(), pred_one);
	std::remove_copy_if(ShapeArray.begin(), ShapeArray.end(), falseResult.begin(), pred_one);
	for (int q = 0; (trueReuslt[q]); ++q)
		EXPECT_TRUE(trueReuslt[q]->area() >= 3200);
	for (int q = 0; (falseResult[q]); ++q)
		EXPECT_TRUE(falseResult[q]->area() < 3200);
}

GTEST_API_ int main(int argc, char* argv[])
{
	srand(time(0));
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");

	return 0;
}

