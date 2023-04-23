#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "lab2.h"

using namespace testing;

TEST(Lab2TestSet, DefaultEllipseTest)
{
    Ellipse *e = new Ellipse(Color(0, 0, 0), Point(0, 0), 10, 100);
    SectorOfEllipse s1_correct(Color(0, 0, 0), Point(0, 0), 10, 100, 0, 0, 120);
    SectorOfEllipse s2_correct(Color(0, 0, 0), Point(0, 0), 10, 100, 0, 120, 240);
    SectorOfEllipse s3_correct(Color(0, 0, 0), Point(0, 0), 10, 100, 0, 240, 360);

    SectorOfEllipse *s1 = new SectorOfEllipse();
    SectorOfEllipse *s2 = new SectorOfEllipse();
    SectorOfEllipse *s3 = new SectorOfEllipse();

    SectorOfEllipse::split(e, s1, s2, s3);

    EXPECT_EQ(*s1, s1_correct);
    EXPECT_EQ(*s2, s2_correct);
    EXPECT_EQ(*s3, s3_correct);

    delete s1;
    delete s2;
    delete s3;
}

TEST(Lab2TestSet, StandartEllipseTest)
{
    Ellipse *e = new Ellipse(Color(100, 255, 32), Point(10, 1), 10, 100, 90);
    SectorOfEllipse s1_correct(Color(100, 0, 0), Point(10, 1), 10, 100, 90, 0, 120);
    SectorOfEllipse s2_correct(Color(0, 255, 0), Point(10, 1), 10, 100, 90, 120, 240);
    SectorOfEllipse s3_correct(Color(0, 0, 32), Point(10, 1), 10, 100, 90, 240, 360);

    SectorOfEllipse *s1 = new SectorOfEllipse();
    SectorOfEllipse *s2 = new SectorOfEllipse();
    SectorOfEllipse *s3 = new SectorOfEllipse();

    SectorOfEllipse::split(e, s1, s2, s3);

    EXPECT_EQ(*s1, s1_correct);
    EXPECT_EQ(*s2, s2_correct);
    EXPECT_EQ(*s3, s3_correct);

    delete s1;
    delete s2;
    delete s3;
}

TEST(Lab2TestSet, SectorOfEllipseTest)
{
    Ellipse *e = new SectorOfEllipse(Color(100, 255, 32), Point(10, 1), 10, 100, 90, 0, 360);
    SectorOfEllipse s1_correct(Color(100, 0, 0), Point(10, 1), 10, 100, 90, 0, 120);
    SectorOfEllipse s2_correct(Color(0, 255, 0), Point(10, 1), 10, 100, 90, 120, 240);
    SectorOfEllipse s3_correct(Color(0, 0, 32), Point(10, 1), 10, 100, 90, 240, 360);

    SectorOfEllipse *s1 = new SectorOfEllipse();
    SectorOfEllipse *s2 = new SectorOfEllipse();
    SectorOfEllipse *s3 = new SectorOfEllipse();

    SectorOfEllipse::split(e, s1, s2, s3);

    EXPECT_EQ(*s1, s1_correct);
    EXPECT_EQ(*s2, s2_correct);
    EXPECT_EQ(*s3, s3_correct);

    delete s1;
    delete s2;
    delete s3;
}
