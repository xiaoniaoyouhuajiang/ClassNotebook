#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../../src/square.h" // + rectangle.h

using namespace testing;

TEST(SquareTestSet, DefaultSquareTest)
{
    Point p(0, 2);
    Square sq(Point(), 1, 0);

    double dist = sq.distance(p);

    EXPECT_FLOAT_EQ(dist, 2);
}

TEST(SquareTestSet, PointInSquareCenterTest)
{
    Point p(0, 0);
    Square sq(Point(-1, 1), 2, 0);

    double dist = sq.distance(p);

    EXPECT_FLOAT_EQ(dist, sqrt(2));
}

TEST(SquareTestSet, TurnedSquareTest)
{
    Point p(1, sqrt(2));
    Square sq(Point(-1, 1), 2, M_PI / 4);

    double dist = sq.distance(p);

    EXPECT_FLOAT_EQ(dist, 1);
}

TEST(SquareTestSet, PointInSquareVertexTest)
{
    Point p(20, 10);
    Square sq(Point(10, 10), 10, 0);

    double dist = sq.distance(p);

    EXPECT_FLOAT_EQ(dist, 0);
}

TEST(SquareTestSet, SquareWithZeroSideTest)
{
    Point p(1, 1);
    Square sq(Point(), 0, 0);

    double dist = sq.distance(p);

    EXPECT_FLOAT_EQ(dist, sqrt(2));
}

TEST(SquareTestSet, SquareWithNegativeSideTest)
{
    ASSERT_THROW( { Square(Point(), -1, 0); }, std::invalid_argument );
}
