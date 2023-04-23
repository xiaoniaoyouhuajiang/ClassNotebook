
#include <gtest/gtest.h>
#include "figure.h"
#define PI 3.14
TEST(RhombusTest, TestRhombus) {
  Rhombus a(100,45*PI/180);
  Rhombus b(2,10*PI/180);
  b.move(Point(10,1));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));
}

TEST(RhombusTest, TestTriangle) {
  Rhombus a(100,50*PI/180);
  Triangle b(2,Point(2,2));
  b.move(Point(1,1));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));

}

TEST(RhombusTest, TestParallelogram) {
  Rhombus a(100,50*PI/180);
  Parallelogram b(2,5);
  b.move(Point(50,50));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));

}

TEST(TriangleTest, TestRhombus) {
  Triangle a(100,Point(20,100));
  Rhombus b(2,10*PI/180);
  b.move(Point(10,1));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));
}

TEST(TriangleTest, TestTriangle) {
  Triangle a(100,Point(20,100));
  Triangle b(2,Point(2,2));
  b.move(Point(1,1));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));

}

TEST(TriangleTest, TestParallelogram) {
  Triangle a(100,Point(20,100));
  Parallelogram b(2,5);
  b.move(Point(50,50));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));

}


TEST(ParallelogramTest, TestRhombus) {
  Parallelogram a(100,60);
  Rhombus b(2,10*PI/180);
  b.move(Point(10,1));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));
}

TEST(ParallelogramTest, TestTriangle) {
  Parallelogram a(100,60);
  Triangle b(2,Point(2,2));
  b.move(Point(1,1));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));

}

TEST(ParallelogramTest, TestParallelogram) {
  Parallelogram a(100,60);
  Parallelogram b(2,5);
  b.move(Point(50,50));
  EXPECT_TRUE(a.isInsideOfAnother(b));

  a.rotate(90*PI/180);
  EXPECT_FALSE(a.isInsideOfAnother(b));
  
  b.move(Point(-1,-0.5));
  EXPECT_FALSE(a.isInsideOfAnother(b));

}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
