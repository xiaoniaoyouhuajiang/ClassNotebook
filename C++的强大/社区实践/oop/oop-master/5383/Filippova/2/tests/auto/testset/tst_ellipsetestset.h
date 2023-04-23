#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../../src/ellipse.h"

using namespace testing;

TEST(EllipseTestSet, PointInEllipseTest)
{
    Point p(0, 1);
    Ellipse e(Point(), 3, 2, 0);

    double dist = e.distance(p);

    EXPECT_FLOAT_EQ(dist, 1);
}

TEST(EllipseTestSet, PointOutsideOfEllipseTest)
{
    Point p(0, -10);
    Ellipse e(Point(), 3, 2, 0);

    double dist = e.distance(p);

    EXPECT_FLOAT_EQ(dist, 8);
}

TEST(EllipseTestSet, TurnedEllipseTest)
{
    Point p(3, 3);
    Ellipse e(Point(), 3, 2, M_PI / 4);

    double dist = e.distance(p);

    EXPECT_FLOAT_EQ(dist, 3 * (sqrt(2) - 1));
}

TEST(EllipseTestSet, PointInEllipseVertexTest)
{
    Point p(-3, 0);
    Ellipse e(Point(), 3, 2, 0);

    double dist = e.distance(p);

    EXPECT_FLOAT_EQ(dist, 0);
}

TEST(EllipseTestSet, EllipseWithZeroSideTest)
{
    Point p(1, 1);
    Ellipse e(Point(), 1, 0, 0);

    double dist = e.distance(p);

    EXPECT_FLOAT_EQ(dist, 1);
}

TEST(EllipseTestSet, EllipseWithNegativeSideTest)
{
    ASSERT_THROW( { Ellipse(Point(), -3, 1, 0); }, std::invalid_argument );
}
