#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../../src/round.h"

using namespace testing;

TEST(Round_Round_TestSet, CircleTwoPoints)
{
    //Round r1(0, 0, 1);
    //Round r2(0, 1, 1);

    //Arc a1(0, 0, 0, 2*M_PI, 3);
    //Arc a2(5, 0, 0, 2*M_PI, 3);

    Round a1(0, 0, 3);
    Round a2(5, 0, 3);

    //int result = r2.intersect(r1);

    int result = a2.intersect(a1);

    EXPECT_EQ(result, 2);
}

TEST(Round_Round_TestSet, CircleOnePoint)
{
    Round r1(1, 1, sqrt(2));
    Round r2(-1, -1, sqrt(2));

    int result = r2.intersect(r1);

    EXPECT_EQ(result, 1);
}

TEST(Round_Round_TestSet, CircleCloseEdges)
{
    Round r1(0, 1, 1);
    Round r2(0, -0.999, 1);

    int result = r2.intersect(r1);

    EXPECT_EQ(result, 2);
}

TEST(Round_Round_TestSet, CircleCloseCenters)
{
    Round r1(1, 0, 1);
    Round r2(0.999, 0, 1);

    int result = r2.intersect(r1);

    EXPECT_EQ(result, 2);
}

TEST(Round_Round_TestSet, SameCircle)
{
    Round r(0, 1, 1);

    int result = r.intersect(r);

    EXPECT_EQ(result, -1);
}

TEST(Round_Round_TestSet, CircleNoPoints)
{
    Round r1(10, 10, 1);
    Round r2(-10, -10, 1);

    int result = r2.intersect(r1);

    EXPECT_EQ(result, 0);
}

TEST(Round_Round_TestSet, CircleZeroRadius)
{
    Round r(0, 0, 1);
    Round z(0, 1, 0);

    int res1 = r.intersect(z);
    int res2 = z.intersect(r);

    EXPECT_EQ(res1, res2);
    EXPECT_EQ(res1, 1);
}

TEST(Round_Ellipse_TestSet, RoundEllipse4Points)
{
    Round r(0, 0, 2);
    Ellipse e(0, 0, 1, 3);

    int result = e.intersect(r);

    EXPECT_EQ(result, 4);
}

TEST(Round_Ellipse_TestSet, RoundRotatedEllipse4Points)
{
    Round r(0, 0, 2);
    Ellipse e(0, 0, 1, 3, M_PI/4);

    int result = e.intersect(r);

    EXPECT_EQ(result, 4);
}

TEST(Round_Ellipse_TestSet, RoundRotatedEllipse2PointsY)
{
    Round r(0, 0, 2);
    Ellipse e(0, 0, 3, 2, M_PI/4);

    int result = e.intersect(r);

    EXPECT_EQ(result, 2);
}

TEST(Round_Ellipse_TestSet, RoundRotatedEllipse2PointsX)
{
    Round r(0, 0, 2);
    Ellipse e(0, 0, 2, 3, M_PI/4);

    int result = e.intersect(r);

    EXPECT_EQ(result, 2);
}

TEST(Ellipse_Ellipse_TestSet, EllipseEllipse4Points)
{
    Ellipse e1(0, 0, 2, 3);
    Ellipse e2(0, 0, 3, 2);

    int result = e2.intersect(e1);

    EXPECT_EQ(result, 4);
}

TEST(Ellipse_Ellipse_TestSet, RotatedEllipseRotatedEllipse4Points)
{
    Ellipse e1(0, 0, 2, 3, M_PI/4);
    Ellipse e2(0, 0, 3, 2, M_PI/4);

    int result = e2.intersect(e1);

    EXPECT_EQ(result, 4);
}

TEST(Arc_Ellipse_TestSet, DefaultArcDefaultEllipse2Points)
{
    Arc a1(0, 0, 0, M_PI/2, 1);
    Ellipse e2(0, 0, 3, 2, 0);

    int result = e2.intersect(a1);

    EXPECT_EQ(result, 0);
}

TEST(Arc_Arc_TestSet, DefaultArcDefaultArc2Points)
{
    Arc a1(5, 0, M_PI/2, 3*M_PI/2, 3);
    Arc a2(0, 0, -M_PI/2, M_PI/2, 3);

    int result = a1.intersect(a2);

    EXPECT_EQ(result, 2);
}


TEST(Arc_Arc_TestSet, DefaultArcDefaultArc1Points)
{
    Arc a1(-5, 0, 0, M_PI, 3);
    Arc a2(-10, 0, 0, M_PI, 3);

    int result = a1.intersect(a2);

    EXPECT_EQ(result, 1);
}

TEST(Round_Arc_TestSet, DefaultRoundDefaultArc2Points)
{
    Round r1(0, 0, 3);
    Arc a1(-5, 0, 0, 2*M_PI, 3);

    int result = a1.intersect(r1);

    EXPECT_EQ(result, 2);
}

TEST(Round_Arc_TestSet, DefaultRoundDefaultArcMach)
{
    Round r1(0, 0, 3);
    Arc a1(0, 0, 0, M_PI, 3);

    int result = r1.intersect(a1);

    EXPECT_EQ(result, -1);
}

TEST(Round_Arc_TestSet, DefaultRoundNegativeCenterArc2points)
{
    Round r1(0, 0, 2);
    Arc a1(-3, 3, -(M_PI/2), M_PI/2, 4);

    int result = a1.intersect(r1);

    EXPECT_EQ(result, 2);
}
