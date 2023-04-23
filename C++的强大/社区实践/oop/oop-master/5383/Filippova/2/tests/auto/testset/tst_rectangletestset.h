#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../../src/rectangle.h"

using namespace testing;

TEST(RectangleTestSet, DefaultRectangleTest)
{
    Point p(0, 2);
    Rectangle rect(Point(), 3, 1, 0);

    double dist = rect.distance(p);

    EXPECT_FLOAT_EQ(dist, 2);
}

TEST(RectangleTestSet, TurnedRectangleTest)
{
    Point p(0, 2);
    Rectangle rect(Point(), 3, 1, M_PI / 2);

    double dist = rect.distance(p);

    EXPECT_FLOAT_EQ(dist, 1);
}

TEST(RectangleTestSet, PointInRectangleCenterTest)
{
    Point p(3, 2);
    Rectangle rect(Point(0, 3), 4, 3, 0);

    double dist = rect.distance(p);

    EXPECT_FLOAT_EQ(dist, sqrt(2));
}

TEST(RectangleTestSet, PointOnRectangleSideTest)
{
    Point p(2, -1);
    Rectangle rect(Point(), 3, 1, 0);

    double dist = rect.distance(p);

    EXPECT_FLOAT_EQ(dist, 1);
}

TEST(RectangleTestSet, PointInRectangleVertexTest)
{
    Point p(4, 0);
    Rectangle rect(Point(0, 3), 4, 3, 0);

    double dist = rect.distance(p);

    EXPECT_FLOAT_EQ(dist, 0);
}

TEST(RectangleTestSet, RectangleWithZeroSideTest)
{
    Point p(0, 2);
    Rectangle rect(Point(1, 1), 2, 0, 0);

    double dist = rect.distance(p);

    EXPECT_FLOAT_EQ(dist, sqrt(2));
}

TEST(RectangleTestSet, RectangleWithNegativeSideTest)
{
    ASSERT_THROW( { Rectangle(Point(), -1, -2, 0); }, std::invalid_argument );
}

