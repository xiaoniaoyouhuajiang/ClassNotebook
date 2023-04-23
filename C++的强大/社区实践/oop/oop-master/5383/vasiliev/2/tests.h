#include <gtest/gtest.h>
#include <shapes.h>

using namespace testing;

TEST(ShapeTest, id)
{
    Rectangle a(1,1);
    EXPECT_EQ(a.getId(), 1);
    Square b(1, 1);
    EXPECT_EQ(b.getId(), 2);
    Ellipse c(1, 1);
    EXPECT_EQ(c.getId(), 3);
}

TEST(RectangleTest, Constructor)
{
    Rectangle s(1,2,Point(3,4),5,0xDEADB33F);
    EXPECT_DOUBLE_EQ(s.getLength(), 1);
    EXPECT_DOUBLE_EQ(s.getWidth(), 2);
    Point p = s.getPosition();
    EXPECT_DOUBLE_EQ(p.x, 3);
    EXPECT_DOUBLE_EQ(p.y, 4);
    EXPECT_DOUBLE_EQ(s.getAngle(), fmod(5, 2 * M_PI));
    EXPECT_EQ(s.getColor(), 0xDEADB33F);
}

TEST(RectangleTest, ThrowConstructor)
{
    EXPECT_THROW(Rectangle(0,0,Point(0,0),0,0), Shape::ConstructError);
}

TEST(RectangleTest, Area)
{
    Rectangle a(3,5.2);
    EXPECT_DOUBLE_EQ(a.getArea(), 15.6);
}

TEST(RectangleTest, Perimeter)
{
    Rectangle a(3,5.2);
    EXPECT_DOUBLE_EQ(a.getPerimeter(), 16.4);
}

TEST(RectangleTest, Stretch)
{
    Rectangle a(3,5.2);
    a.stretch(4.8);
    EXPECT_DOUBLE_EQ(a.getLength(), 14.4);
    EXPECT_DOUBLE_EQ(a.getWidth(), 24.96);
    a.stretchLength(2);
    EXPECT_DOUBLE_EQ(a.getLength(), 28.8);
    a.stretchWidth(3);
    EXPECT_DOUBLE_EQ(a.getWidth(), 74.88);
}

TEST(SquareTest, Constructor)
{
    Square s(15,Point(3,4),5,0xDEADB33F);
    EXPECT_DOUBLE_EQ(s.getLength(), 15);
    EXPECT_DOUBLE_EQ(s.getWidth(), 15);
    Point p = s.getPosition();
    EXPECT_DOUBLE_EQ(p.x, 3);
    EXPECT_DOUBLE_EQ(p.y, 4);
    EXPECT_DOUBLE_EQ(s.getAngle(), fmod(5, 2 * M_PI));
    EXPECT_EQ(s.getColor(), 0xDEADB33F);
}

TEST(SquareTest, Stretch)
{
    Square a(3);
    a.stretch(4.8);
    EXPECT_DOUBLE_EQ(a.getLength(), 14.4);
    EXPECT_DOUBLE_EQ(a.getWidth(), 14.4);
    EXPECT_THROW(a.stretchLength(2),Shape::IllegalMethod);
    EXPECT_THROW(a.stretchWidth(3),Shape::IllegalMethod);
}

TEST(EllipseTest, Area)
{
    Ellipse a(3,5.2);
    EXPECT_DOUBLE_EQ(a.getArea(), 12.252211349000193);
}

TEST(EllipseTest, Perimeter)
{
    Ellipse a(3,5.2);
    EXPECT_DOUBLE_EQ(a.getPerimeter(), 13.026547657561165);
}
