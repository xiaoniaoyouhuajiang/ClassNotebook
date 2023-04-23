#include "Shapes.h"
#include "gtest/gtest.h"

TEST(shape_test,test1) {
    Arc arc (Point (1.0,1.0), Point (2.0,2.0), 90, red);
    Ellipse ellipse (Point (10.0,-10.0), Point (15.0,-15.0), blue);

    EXPECT_FALSE(arc.doinsert(ellipse));
}

TEST(shape_test, test2) {
    Circle circle (Point (1.5,2.5), 5.0, blue);
    Ellipse ellipse (Point (-10.0,10.0), Point (10.0, -10.0), green);

    EXPECT_TRUE(ellipse.doinsert(circle));
}

TEST(shape_test, test3) {
    Ellipse ellipse (Point (-10.0,10.0), Point (10.0, -10.0), green);

    EXPECT_TRUE(ellipse.doinsert(ellipse));
}

TEST(shape_test, test4) {
    Arc arc (Point (1.0,1.0), Point (2.0,2.0), 90, red);
    Circle circle (Point (0.0,0.0), 2.0, blue);

    EXPECT_TRUE(arc.doinsert(circle));
}

TEST(shape_test, test5) {
    Arc arc (Point (1.0,1.0), Point (2.0,2.0), 90, red);
    Circle circle (Point (0.0,0.0), 2.0, blue);

    EXPECT_TRUE(circle.doinsert(arc));
}

TEST(shape_test, test6) {
    Circle circle (Point (-10,2.5), 5.0, blue);
    Ellipse ellipse (Point (10.0,10.0), Point (0, -10.0), green);

    EXPECT_FALSE(circle.doinsert(ellipse));
}